<?php

/**
 * Page callback for the 'goauth/authenticate' path.
 *
 * This page callback does every kind of authorizations.
 */
function google_drive_sync_authenticate_page() {
  $code = isset($_GET['code']) ? $_GET['code'] : NULL;

  $handler = new GoogleDriveAuthHandler(
    variable_get('googledrive_client_id'),
    variable_get('googledrive_client_secret'),
    variable_get('googledrive_redirect_uri')
  );

  if (!isset($_SESSION['redeemed_codes'])) {
    $_SESSION['redeemed_codes'] = array();
  }
  $handler->Verify($code, $_SESSION['redeemed_codes']);
  $_SESSION['redeemed_codes'][] = $code;

  drupal_goto('<front>');
}

/**
 * Admin form.
 */
function google_drive_sync_admin_auth_form() {
  $form = array();

  $form['googledrive_client_id'] = array(
    '#title' => t('Client ID'),
    '#type' => 'textfield',
    '#default_value' => variable_get('googledrive_client_id'),
  );

  $form['googledrive_client_secret'] = array(
    '#title' => t('Client Secret'),
    '#type' => 'textfield',
    '#default_value' => variable_get('googledrive_client_secret'),
  );

  $form['googledrive_redirect_uri'] = array(
    '#title' => t('Redirect URI'),
    '#type' => 'textfield',
    '#default_value' => variable_get('googledrive_redirect_uri'),
  );

  $form['googledrive_auto_sync'] = array(
    '#title' => t('Automatic document synchronization from Google Drive'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('googledrive_auto_sync', 0),
  );

  return system_settings_form($form);
}
