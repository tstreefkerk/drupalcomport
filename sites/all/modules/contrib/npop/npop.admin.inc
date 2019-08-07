<?php

/**
 * @file
 * Node popup module administration pages functions.
 */

/**
 * Main administration settings page form.
 */
function npop_admin_settings_form($form, $form_state) {
  $node_types = node_type_get_names();
  $form['npop_change_urls'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Change urls on selected node types'),
    '#default_value' => variable_get('npop_change_urls', array()),
    '#description' => t('Allow to change url (by JavaScript History API), for selected node types, when popup window is oppen. This is SEO friendly settings for popup window.'),
    '#options' => $node_types,
  );

  // Allow other modules create animations for popup window.
  $animations = array_map('_npop_fix_css_arrays', module_invoke_all('npop_css_animations'));
  $form['npop_animations'] = array(
    '#type' => 'select',
    '#options' => $animations,
    '#default_value' => variable_get('npop_animations'),
    '#empty_option' => t('Without animation'),
    '#empty_value' => 0,
  );

  // Allow to override close link text.
  $form['npop_close_override'] = array(
    '#title' => t('Override close link.'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('npop_close_override', FALSE),
  );
  $form['npop_close_override_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Close link text'),
    '#states' => array(
      'visible' => array(
        ':input[name="npop_close_override"]' => array('checked' => TRUE),
      ),
      'required' => array(
        ':input[name="npop_close_override"]' => array('checked' => TRUE),
      ),
    ),
    '#description' => t('Allow to use HTML for link text'),
    '#default_value' => variable_get('npop_close_override_text', ''),
  );

  $form['npop_overlay_close'] = array(
    '#type' => 'checkbox',
    '#title' => t('Close by overlay click'),
    '#default_value' => variable_get('npop_overlay_close', 1),
  );

  $form['#validate'][] = 'npop_validate_admin_settings_form';
  // Fitler saved values.
  $form['array_filter'] = array(
    '#type' => 'value',
    '#value' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Validate admin settings form.
 * Check the overrided text not empty.
 * @see npop_admin_settings_form().
 */
function npop_validate_admin_settings_form(&$form, &$form_state) {
  $is_override = $form_state['values']['npop_close_override'];
  if ($is_override) {
    $override_text = trim($form_state['values']['npop_close_override_text']);
    if (empty($override_text)) {
      form_set_error('npop_close_override_text', t('Fill the close link text if override text checked'));
    }
  }
}

/**
 * The array_map callback functoin, fixed duplicate class names.
 */
function _npop_fix_css_arrays($element) {
  if (is_array($element)) {
    return array_shift($element);
  }
  else {
    return $element;
  }
}
