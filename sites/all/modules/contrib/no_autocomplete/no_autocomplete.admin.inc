<?php

/**
 * @file
 * Calls results to administration's pages for the No Autocomplete module.
 */

/**
 * Form constructor for No autocomplete form.
 *
 * @param array $form
 *   The form element.
 * @param array $form_state
 *   The form state.
 */
function no_autocomplete_admin_settings_form(array $form, array &$form_state) {
  $form['no_autocomplete_login_form'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use "autocomplete=off" on user login form'),
    '#default_value' => variable_get('no_autocomplete_login_form'),
  );

  $form = system_settings_form($form);

  return $form;
}
