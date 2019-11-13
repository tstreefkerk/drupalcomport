INTRODUCTION
------------

The Google PHP Client Library module provides a quick use of the hooks provided by Libraries API to enable the library for general use, together with drush features such as auto-downloading of the library when the module is downloaded via drush and a drush command to download the library if the module wasn't downloaded via drush.

 * For a full description of the module, visit the project page:
   https://drupal.org/project/google_php_client_library

 * To submit bug reports and feature suggestions, or to track changes:
   https://drupal.org/project/issues/google_php_client_library

REQUIREMENTS
------------

 1. Libraries API - This modules depends on libraries apis module.
 You can download from http://drupal.org/project/libraries

 2. Google client library - You need to download google api php client library
 from https://github.com/google/google-api-php-client/releases

INSTALLATION
------------

  * Download the latest release of google php client library from
     https://github.com/google/google-api-php-client/releases and
     extract it in libraries folder of the site, mostly located at
     sites/all/libraries, the path is
    'sites/all/libraries/google-api-php-client/src..'

  * You may use composer to install without downloading the file which is fine.
    The final path after installation should be 'sites/all/libraries/google-api-php-client'

  * In case of normal release install it will have src folder and incase of composer it won't have that.

  * Note that the module will only work with google-api-php-client 2.1.0 or later.

  * Some common problems may relate to the lib folder permissions and Drupal cache.


CONFIGURATION
-------------

The module has no menu or modifiable settings. There is no configuration.
