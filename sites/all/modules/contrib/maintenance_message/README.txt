INTRODUCTION
------------

This module displays a message on the login
page when your website is in maintenance mode.
It adds a field to the normal maintenance mode form
so admins can configure a different message to admins
than to authenticated users.
By default, Drupal does not show this message on
the login page, which is a problem for websites
that only have registered users. This module sets
that message on the login page as a warning.
This module has been developed for websites
where the user always needs to login,
such as business portals.
This module requires no other modules.
The code simply checks if a message has been
set by the user, and if none has been set it
sets a translatable default message.

For a full description of the module, visit the project page:
 https://www.drupal.org/sandbox/tobias.streefkerk/2646854

To submit bug reports and feature suggestions, or to track changes:
 https://www.drupal.org/project/issues/2646854


REQUIREMENTS
------------

No special requirements.


INSTALLATION
------------

 * Install as you would normally install a contributed Drupal module. See:
   https://www.drupal.org/sandbox/tobias.streefkerk/2646854
   for further information.


CONFIGURATION
-------------

 *Configure maintenance mode permissions in People > Permissions

 *Set message for login screen at the second form under admin/config/development
  /maintenance

 *Put website into maintenance mode at admin/config/development/maintenance

 *After you're done, disable maintenance mode at admin/config/development/
  maintenance


MAINTAINERS
-----------

Current maintainers:
 * Tobias Streefkerk (tobias.streefkerk) - https://www.drupal.org/user/3299401/


TROUBLESHOOTING
---------------

 * Best practices:
    -   Turn on maintenance mode only on end websites.
        It is not necessary to do so on your local website.
    -   Enter a message. This module uses that message
        for users.
    -   Do NOT forget to turn off maintenance mode when
        you're done. Users will not be able log in when your
        site is in maintenance mode.
    -   Make very sure that you give (only) administrators
        the rights to log in while in maintenance mode.
        It defeats the purpose otherwise or you will not be able
        to log in.
        Installation: place these files either under sites/all/modules
        or sites/all/modules/contrib, depending on what file structure
        you are using. You can also use Drupals installer on your own
        website by going to admin/modules.
