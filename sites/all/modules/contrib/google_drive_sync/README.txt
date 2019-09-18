This module synchronize the documents from Google Drive into Drupal nodes.
Files won't be downloaded, just a reference will be saved.

The module contains a features called cloud_asset, which creates the
necessary content type for the Google Drive Synchronization module.

REQUIREMENTS
------------

The module uses the Google APIs client library for PHP. You can find it on
the following url: https://code.google.com/p/google-api-php-client/

The module also has dependencies with the following contributed ones:
- Libraries
- Features

INSTALLATION
------------

1. Download the module from drupal.org, and place it somewhere in the
'sites/all/modules/' directory.
2. Download the Google APIs clint library for PHP, and place it under the
'sites/all/libraries' directory.
3. Download the necessary contributed modules.
4. Enabled the Google Drive Synchronization module on module setting's page.
5. Set the Client ID, Client Secret and the Redirect URI on Google Drive
authentication setting's page(admin/config/people/googledrive). The Redirect URI
is always the following: http://your-domain/goauth/authenticate.
You have to set it in your google app as well.
