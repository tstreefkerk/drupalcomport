<?php

/**
 * Authorization handler for Google Drive.
 */
class GoogleDriveAuthHandler {

  /**
   * Client ID.
   *
   * @var string
   */
  private $clientID;

  /**
   * Client secret
   *
   * @var string
   */
  private $clientSecret;

  /**
   * Redirection URI.
   *
   * @var string
   */
  private $redirectURI;

  /**
   * Credentials.
   *
   * @var string
   */
  private $credentials;

  /**
   * Loads the required libraries.
   */
  protected static function loadLib() {
    static $done = FALSE;

    if (!$done) {
      $base = realpath('.') . '/' . libraries_get_path('google-api-php-client') . '/src';
      require_once "{$base}/Google_Client.php";
      require_once "{$base}/auth/Google_OAuth2.php";
      require_once "{$base}/contrib/Google_Oauth2Service.php";
      $done = TRUE;
    }
  }

  /**
   * @constructor
   *
   * @param string $clientID
   * @param string $clientSecret
   * @param string $redirectURI
   */
  public function __construct($clientID, $clientSecret, $redirectURI) {
    $this->clientID = $clientID;
    $this->clientSecret = $clientSecret;
    $this->redirectURI = $redirectURI;

    self::loadLib();
  }

  /**
   * Builds and returns a client manager object.
   *
   * @return Google_Client
   */
  protected function getClient() {
    $client = new Google_Client();
    $client->setClientId($this->clientID);
    $client->setClientSecret($this->clientSecret);
    $client->setRedirectUri($this->redirectURI);

    return $client;
  }

  /**
   * Fetches the OAuth credentials from Google.
   *
   * @param string $code
   *   Code from the request.
   *
   * @return array
   *   Fetched credentials.
   */
  public function GetOAuthCredentials($code) {
    $client = $this->getClient();

    $credentials = json_decode($client->authenticate($code));

    return array(
      'access_token' => $credentials->access_token,
      'token_type' => $credentials->token_type,
      'id_token' => $credentials->id_token,
      'refresh_token' => isset($credentials->refresh_token) ?
        $credentials->refresh_token : NULL,
      'created' => $credentials->created,
      'expires_in' => $credentials->expires_in,
      'client_id' => $this->clientID,
      'client_secret' => $this->clientSecret,
    );
  }

  /**
   * Fetches user information from Google.
   *
   * @param $credentials
   *   Credentials from $this->GetOAuthCredentials().
   *
   * @return array
   *   User information.
   */
  public function GetUserInfo($credentials) {
    $client = $this->getClient();
    $client->setAccessToken(json_encode($credentials));

    $infoService = new Google_Oauth2Service($client);
    return $infoService->userinfo->get();
  }

  /**
   * Finds or creates a Drupal user and logs it in.
   *
   * @param $userInfo
   *   User information from $this->GetUserInfo().
   * @param $credentials
   *   Credentials from $this->GetOAuthCredentials().
   *
   * @return stdClass|null
   *   User object or NULL on failure.
   */
  public function GetUser($userInfo, $credentials) {
    global $user;
    $account = $user;

    $googledrive = array_filter($credentials + array(
      'id' => $userInfo['id'],
    ));

    if ($account->uid) {
      $account->googledrive = $googledrive;
      user_save($account);
    }
    else {
      if ($uid = db_query('SELECT uid FROM {google_oauth} WHERE id = :id', array(':id' => $userInfo['id']))->fetchField()) {
        $account = user_load($uid);
        if (!$account) {
          return NULL;
        }
        $account->googledrive = $googledrive;
        user_save($account);
      }
      elseif ($uid = db_query('SELECT uid FROM {users} WHERE mail = :mail', array(':mail' => $userInfo['email']))->fetchField()) {
        $account = user_load($uid);
        if (!$account) {
          return NULL;
        }
        $account->googledrive = $googledrive;
        user_save($account);
      }
      else { // Register a new user
        $account = entity_create('user', array(
          'mail' => $userInfo['email'],
          'name' => "{$userInfo['family_name']} {$userInfo['given_name']}",
          'status' => 1,
          'googledrive' => $googledrive,
          'init' => $userInfo['email'],
        ));
        user_save($account);
      }
      $form_state['uid'] = $account->uid;
      user_login_submit(array(), $form_state);
    }

    return $account;
  }

  /**
   * Verifies a code.
   *
   * If the verification succeeds, creates or finds a Drupal user and logs it in.
   *
   * @param string $code
   *   Code from Google's OAuth system.
   * @param array $redeemed_codes
   *   List of recently used codes. Usually stored in $_SESSION. This prevents
   *   attempting to reuse the same code twice (because of user page reloading).
   *
   * @return null|stdClass
   *   User object on success, NULL on failure.
   */
  public function Verify($code, array $redeemed_codes) {
    $userInfo = NULL;

    if (array_search($code, $redeemed_codes) === FALSE) {
      $credentials = $this->GetOAuthCredentials($code);

      try {
        $userInfo = $this->GetUserInfo($credentials);
      } catch (Exception $e) {
        watchdog_exception('GoogleDrive', $e, $e->getMessage(), array(), WATCHDOG_ERROR);
      }

      try {
        $account = $this->GetUser($userInfo, $credentials);
        return $account;
      } catch (Exception $e) {
        watchdog_exception('GoogleDrive', $e, $e->getMessage(), array(), WATCHDOG_ERROR);
      }
    }

    return NULL;
  }

}
