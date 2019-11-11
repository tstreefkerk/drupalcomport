<?php

/**
 * @file
 *   Google API drush commands.
 *
 */

/**
 * Implementation of hook_drush_command().
 *
 * In this hook, you specify which commands your
 * drush module makes available, what it does and
 * description.
 *
 * Notice how this structure closely resembles how
 * you define menu hooks.
 *
 * See `drush topic docs-commands` for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function google_api_drush_command() {
  $items = array();

  $items['google-api-get'] = array(
    'description' => "Downloads and extracts the Google API Client Library for PHP",
    'arguments' => array(
      'path' => dt('Optional. A path to the download folder. If omitted Drush will use the default location (sites/all/libraries/google-api-php-client).'),
    ),
    'examples' => array(
      'drush gapi' => 'Downloads and extracts the Google API Client.'
    ),
    'aliases' => array('gapi'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap at all.
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'. This hook is optional. If a command
 * does not implement this hook, the command's description is used instead.
 *
 * This hook is also used to look up help metadata, such as help
 * category title and summary.  See the comments below for a description.
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function google_api_drush_help($section) {
  switch ($section) {
    case 'drush:google-api-get':
      return dt("Download the Google API Client Library for PHP and put it into your libraries folder");
  }
}

/**
 * A command callback.
 */
function drush_google_api_get() {
  $library = libraries_detect('google-api-php-client');

  if ($library['installed']) {
    drush_log(dt('Google API Client for PHP (version @version) is already present. No download required.', array('@version' => $library['version'])), 'ok');
  }
  else {
    $args = func_get_args();
    $path = drush_get_context('DRUSH_DRUPAL_ROOT') . '/' . (isset($args[0]) ? $args[0] : 'sites/all/libraries/google-api-php-client');

    if (drush_shell_exec('git clone -b v1-master --single-branch https://github.com/google/google-api-php-client.git ' . escapeshellarg($path))) {
      drush_log(dt('Google API Client for PHP has been exported via git to @path.', array('@path' => $path)), 'success');
    }
    else {
      drush_log(dt('Drush was unable to export Google API Client for PHP to @path.', array('@path' => $path)), 'warning');
    }
  }
}

/**
 * Implements drush_MODULE_post_COMMAND().
 */
function drush_google_api_post_pm_enable() {
  $extensions = func_get_args();
  // Deal with comma delimited extension list.
  if (strpos($extensions[0], ',') !== FALSE) {
    $extensions = explode(',', $extensions[0]);
  }

  if (in_array('google_api', $extensions) && !drush_get_option('skip')) {
    drush_google_api_get();
  }
}

