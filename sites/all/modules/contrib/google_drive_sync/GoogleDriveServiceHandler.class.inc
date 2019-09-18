<?php

/**
 * Service handler for Google Drive.
 */
class GoogleDriveServiceHandler extends GoogleDriveAuthHandler {

  /**
   * Loads the required libraries.
   */
  protected static function loadServiceLib() {
    static $done = FALSE;

    if (!$done) {
      $base = realpath('.') . '/' . libraries_get_path('google-api-php-client') . '/src';
      require_once "{$base}/contrib/Google_DriveService.php";
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
    $handler = parent::__construct($clientID, $clientSecret, $redirectURI);
    self::loadServiceLib();
  }

  /**
   * Create a service with the given user credentials.
   *
   * @param array $credentials
   *   Given user informations.
   *
   * @return Google_DriveService
   *   The created service object.
   */
  public function buildService($credentials) {
    $apiClient = $this->getClient();
    $apiClient->setScopes(array('https://www.googleapis.com/auth/drive'));
    $apiClient->setUseObjects(TRUE);
    $apiClient->setAccessToken(json_encode($credentials));

    return new Google_DriveService($apiClient);
  }

  /**
   * Return all of the files for a service. Conditions can be added to the query.
   *
   * @param $service
   * @param null $conditions
   * @return array
   */
  public function getFiles($service, $conditions = NULL) {
    $result = array();
    $parameters = array();
    $pageToken = NULL;

    do {
      try {
        if ($pageToken) {
          $parameters['pageToken'] = $pageToken;
        }
        if ($conditions) {
          $parameters['q'] = $conditions;
        }

        $files = $service->files->listFiles($parameters);

        $result = array_merge($result, $files->getItems());
        $pageToken = $files->getNextPageToken();
      } catch(Exception $e) {
        watchdog_exception('GoogleDrive', $e, $e->getMessage(), array(), WATCHDOG_ERROR);
      }
    } while ($pageToken);

    return $result;
  }
}
