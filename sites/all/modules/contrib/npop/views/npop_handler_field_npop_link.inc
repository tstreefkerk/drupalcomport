<?php

/**
 * @file
 * Views handlers for Node popup(npop) module.
 */

/**
 * A handler to provide a field that is completely custom by the administrator.
 *
 * @ingroup views_field_handlers
 */
class npop_handler_field_npop_link extends views_handler_field_node_link {

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
  }

  /**
   * Apply our colorbox-node class and add width and height to the query params.
   */
  function render_link($node, $values) {
    if (!empty($this->options['node_to_npop']) && node_access('view', $node)) {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = 'node/' . $node->nid;
      $text = !empty($this->options['text']) ? $this->options['text'] : t('view');
      $this->options['alter']['link_attributes']['data-npop'] = $node->nid;
      return $text;
    }

    return parent::render_link($node, $values);
  }

}
