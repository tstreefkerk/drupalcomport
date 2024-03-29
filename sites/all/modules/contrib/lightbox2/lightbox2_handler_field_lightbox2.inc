<?php
/**
 * @file
 * Contain the integration with views
 * A handler to provide a field that is completely custom by the administrator.
 *
 * @ingroup views_field_handlers
 */
class lightbox2_handler_field_lightbox2 extends views_handler_field {
  function query() {
    // Do nothing, as this handler does not need to do anything to the query itself.
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['trigger_field'] = array('default' => '');
    $options['popup'] = array('default' => '');
    $options['caption'] = array('default' => '');
    $options['rel_group'] = array('default' => TRUE);
    $options['custom_group'] = array('default' => '');
    $options['height'] = array('default' => '400px');
    $options['width'] = array('default' => '600px');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $fields = array('trigger_field' => t('<None>'));
    foreach ($this->view->display_handler->get_handlers('field') as $field => $handler) {
      // Borrowed from colorbox module.
      $options[t('Fields')]["[$field]"] = $handler->ui_name();
      // We only use fields up to this one.  Obviously we can't use this handler
      // as the trigger handler.
      if ($field == $this->options['id']) {
        break;
      }
      $fields[$field] = $handler->definition['title'];
    }
   // Borrowed from colorbox module.
   $count = 0; // This lets us prepare the key as we want it printed.
    foreach ($this->view->display_handler->get_handlers('argument') as $arg => $handler) {
      $options[t('Arguments')]['%' . ++$count] = t('@argument title', array('@argument' => $handler->ui_name()));
      $options[t('Arguments')]['!' . $count] = t('@argument input', array('@argument' => $handler->ui_name()));
    }


    $this->document_self_tokens($options[t('Fields')]);
    
    // Borrowed from colorbox module.
    // Default text.
    $patterns = t('<p>You must add some additional fields to this display before using this field. These fields may be marked as <em>Exclude from display</em> if you prefer. Note that due to rendering order, you cannot use fields that come after this field; if you need a field not listed here, rearrange your fields.</p>');
    // We have some options, so make a list.
    if (!empty($options)) {
      $patterns = t('<p>The following tokens are available for this field. Note that due to rendering order, you cannot use fields that come after this field; if you need a field not listed here, rearrange your fields.
If you would like to have the characters %5B and %5D please use the html entity codes \'%5B\' or  \'%5D\' or they will get replaced with empty space.</p>');
      foreach (array_keys($options) as $type) {
        if (!empty($options[$type])) {
          $items = array();
          foreach ($options[$type] as $key => $value) {
            $items[] = $key . ' == ' . $value;
          }
          $patterns .= theme('item_list',
            array(
              'items' => $items,
              'type' => $type
            ));
        }
      }
    }

    $form['trigger_field'] = array(
      '#type' => 'select',
      '#title' => t('Trigger field'),
      '#description' => t('Select the field that should be turned into the trigger for the lightbox.  Only fields that appear before this one in the field list may be used.'),
      '#options' => $fields,
      '#default_value' => $this->options['trigger_field'],
      '#weight' => -12,
    );

    $form['popup'] = array(
      '#type' => 'textarea',
      '#title' => t('Popup'),
      '#description' => t('Combine tokens from the "Replacement patterns" below and html to create what the lightbox popup will become.'),
      '#default_value' => $this->options['popup'],
      '#weight' => -11,
    );

    $form['caption'] = array(
      '#type' => 'textfield',
      '#title' => t('Caption'),
      '#description' => t('Combine tokens from the "Replacement patterns" below and html to create the caption shown under the lightbox. Leave empty for no caption.'),
      '#default_value' => $this->options['caption'],
      '#weight' => -10,
    );

    $form['rel_group'] = array(
      '#type' => 'checkbox',
      '#title' => t('Automatic generated Lightbox group'),
      '#description' => t('Enable Lightbox grouping using a generated group name for this view.'),
      '#default_value' => $this->options['rel_group'],
      '#weight' => -9,
    );

    $form['custom_group'] = array(
      '#type' => 'textfield',
      '#title' => t('Custom Lightbox group'),
      '#description' => t('Enable Lightbox grouping with a given string as group. Overrides the automatically generated group name above.'),
      '#default_value' => $this->options['custom_group'],
      '#weight' => -8,
    );

    $form['height'] = array(
      '#type' => 'textfield',
      '#title' => t('Height'),
      '#description' => t('Specify the height of the lightbox2 popup window.  Because the content is dynamic, we cannot detect this value automatically.'),
      '#default_value' => $this->options['height'],
      '#weight' => -7,
    );

    $form['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Width'),
      '#description' => t('Specify the width of the lightbox2 popup window.  Because the content is dynamic, we cannot detect this value automatically.'),
      '#default_value' => $this->options['width'],
      '#weight' => -6,
    );
   
   $form['patterns'] = array(
      '#type' => 'fieldset',
      '#title' => t('Replacement patterns'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#value' => $patterns,
    );


    // Remove the checkboxs and other irrelevant controls.
    unset($form['alter']['alter_text']);
    unset($form['alter']['make_link']);
    unset($form['alter']['text']);
    unset($form['alter']['path']);
    unset($form['alter']['alt']);
    unset($form['alter']['prefix']);
    unset($form['alter']['suffix']);
    unset($form['alter']['text']['#dependency']);
    unset($form['alter']['text']['#process']);
  }

  /**
   * Render the trigger field and its linked popup information.
   */
  function render($values) {
    // We need to have multiple unique IDs, one for each record.
    static $i = 0;

    static $link;

    if (!empty($this->options['trigger_field'])) {

      // We don't actually use the link, but we need it there for lightbox to function.
      if (empty($link)) {
        // Get the path name.
        $url = isset($_GET['q']) ? $_GET : '<front>';
        $path = '';
        $params = array();

        //Get the path and any parameters from the URL
        foreach ($url as $key => $value) {
          if ($key === 'q') {
            $path = $value;
          } else {
            $params[$key] = $value;
          }
        }

        $link = url($path, array('absolute' => TRUE, 'query' => $params));
      }

      // Get the token information and generate the value for the popup and the
      // caption.
      $tokens = $this->get_render_tokens($this->options['alter']);
      $popup = filter_xss_admin($this->options['popup']);
      $caption = filter_xss_admin($this->options['caption']);
      $popup = strtr($popup, $tokens);
      $caption = strtr($caption, $tokens);

      $i++;

      // The outside div is there to hide all of the divs because if the specific lightbox
      // div is hidden it won't show up as a lightbox.  We also specify a group
      // in the rel attribute in order to link the whole View together for paging.
      $group_name = !empty($this->options['custom_group']) ? $this->options['custom_group'] : ($this->options['rel_group'] ? 'lightbox-popup-' . $this->view->name . '-' . implode('/', $this->view->args) : '');
      $group_name = check_plain($group_name);
      $width = $this->options['width'] ? check_plain($this->options['width']) : '600px';
      $height = $this->options['height'] ? check_plain($this->options['height']) : '600px';
      $trigger_field = filter_xss_admin($this->options['trigger_field']);

      return "<a href='$link #lightbox-popup-{$i}'  rel='lightmodal[{$group_name}|width:" . $width . ';height:' . $height . "][" . $caption . "]'>" . $tokens["[{$trigger_field}]"] . "</a>
                <div style='display: none;'><div id='lightbox-popup-{$i}' class='lightbox-popup'>$popup</div></div>";
    }
    else {
      return;
    }
  }
}
