INTRODUCTION
------------

Provides Libraries API support for Google API Client Library for PHP - version 1, not 2.
Use the module if you want a quick and easy way of obtaining and using the library.

After installation, you can download the Google API Client Library with Drush:

  > drush google-api-get
  
After enabling the module, you can load the Google API Client Library using
the normal library loading. 

Example using the Youtube service:

  libraries_load('google-api-php-client');
  // Configure the client
  $client = new Google_Client();
  $client->setApplicationName("SomeWebsite");
  $client->setDeveloperKey("SomeKey");
  // Set the include path so we can require different services 
  // without giving the absolute path.
  $glib_info = libraries_info('google-api-php-client');
  $glib_path = libraries_get_path('google-api-php-client');
  set_include_path(get_include_path() . PATH_SEPARATOR . DRUPAL_ROOT . '/' . $glib_path . '/' . $glib_info['path']);
  // Require the Google services you need.
  require_once 'Google/Service/YouTube.php';
  $service = new Google_Service_YouTube($client);

PS! The module will switch to using autoload in later versions.

INSTALLATION
------------

Install as usual, see https://drupal.org/documentation/install/modules-themes/modules-7 
for further information.


MAINTAINERS
-----------

Current maintainers:

 * Hans Nordhaug (https://www.drupal.org/u/hansfn)