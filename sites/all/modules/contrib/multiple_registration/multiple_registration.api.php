<?php

/**
 * @file
 * Multiple Registration module API file.
 */

/**
 * Role-specific registration form alter hook.
 */
function hook_multiple_registration_form_alter(&$form, &$form_state, $rid) {
  $power_user = user_role_load_by_name('Power user');
  if (isset($power_user->rid) && $power_user->rid == $rid) {
    // Update form.
  }
}
