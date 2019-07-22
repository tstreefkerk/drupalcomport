<?php

use Nascom\OAuth2\Client\Provider\Teamleader;
use League\OAuth2\Client\Provider\Exception\IdentityProviderException;

/**
 * Form constructor for the Teamleader administration form.
 */
function teamleader_admin_form($form, &$form_state) {
  // Return callback teamleader
  if (isset($_GET['code'])) {
    if (empty($_GET['state']) || (isset($_SESSION['oauth2state']) && $_GET['state'] !== $_SESSION['oauth2state'])) {
      if (isset($_SESSION['oauth2state'])) {
        unset($_SESSION['oauth2state']);
      }
      drupal_set_message('Invalid state');
    }
    else {
      try {
        $client_id = variable_get('teamleader_client_id');
        $client_secret = variable_get('teamleader_client_secret');
        $current_path = url(current_path(), array('absolute' => TRUE));

        // Create provider
        $provider = new Teamleader([
          'clientId' => $client_id,
          'clientSecret' => $client_secret,
          'redirectUri' => $current_path
        ]);

        $accessToken = $provider->getAccessToken('authorization_code', ['code' => $_GET['code']]);
        variable_set('teamleader_access_token', $accessToken->jsonSerialize());

        drupal_set_message('Successfully connected.');
        drupal_goto($current_path);
      } catch (IdentityProviderException $e) {
        drupal_set_message('Connection failed.');
      }
    }
  }

  // Settings form
  $form = array();

  $form['teamleader_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Teamleader client ID'),
    '#default_value' => variable_get('teamleader_client_id'),
    '#maxlength' => 32,
    '#size' => 36,
  );

  $form['teamleader_client_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Teamleader client secret'),
    '#default_value' => variable_get('teamleader_client_secret'),
    '#maxlength' => 32,
    '#size' => 36,
  );

  $form['#submit'][] = 'teamleader_authorize';

  return system_settings_form($form);
}

/**
 * Authorize integration.
 */
function teamleader_authorize($form, &$form_state) {
  $client_id = $form_state['values']['teamleader_client_id'];
  $client_secret = $form_state['values']['teamleader_client_secret'];

  if (!empty($client_id) && !empty($client_secret)) {
    // Set client ID and secret
    variable_set('teamleader_client_id', $client_id);
    variable_set('teamleader_client_secret', $client_secret);

    // Clear the old access token
    variable_set('teamleader_access_token', '');
    unset($_SESSION['oauth2state']);

    // Request a new one
    $current_path = url(current_path(), array('absolute' => TRUE));

    // Create provider
    $provider = new Teamleader([
      'clientId' => $client_id,
      'clientSecret' => $client_secret,
      'redirectUri' => $current_path
    ]);

    $authorizationUrl = $provider->getAuthorizationUrl();
    $_SESSION['oauth2state'] = $provider->getState();
    drupal_goto($authorizationUrl, array('external' => TRUE));
  }
}
