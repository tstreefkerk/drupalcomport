<?php

/**
 * @file
 * Views handlers for Node popup module.
 */

/**
 * A handler to provide a field that is completely custom by the administrator.
 *
 * @ingroup views_field_handlers.
 */
class npop_handler_field_npop extends views_handler_field_node {

  /**
   * Public function optiondefinition.
   *
   * @return array
   *   Public function optiondefinition array.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['node_to_npop'] = array('default' => isset($this->definition['node_to_npop default']) ? $this->definition['node_to_npop default'] : FALSE, 'bool' => FALSE);
    return $options;
  }

  /**
   * Provide node in colorbox option.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['link_to_node']['#weight'] = -90;
    $form['node_to_npop'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display the content inside of a popup window (Node popup).'),
      '#description' => t("Enable if you want show node in popup window."),
      '#default_value' => !empty($this->options['node_to_npop']),
      '#dependency' => array(
        'edit-options-link-to-node' => array(1),
      ),
      '#weight' => -80,
    );

    $form['alter']['path']['#states']['disabled'] = array(
      ':input[name="options[node_to_npop]"]' => array('checked' => TRUE),
    );
  }

  /**
   * Change node link to npop link to the query params.
   */
  function render_link($data, $values) {
    parent::render_link($data, $values);
    if (!empty($this->options['link_to_node']) && !empty($this->additional_fields['nid'])) {
      if (!empty($this->options['node_to_npop'])) {
        $nid = $this->get_value($values, 'nid');
        $this->options['alter']['path'] = 'node/' . $nid;
        $this->options['alter']['link_attributes']['data-npop'] = $nid;
      }
    }
    return $data;
  }

}
