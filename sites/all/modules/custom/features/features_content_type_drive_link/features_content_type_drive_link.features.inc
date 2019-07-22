<?php

/**
 * @file
 * features_content_type_drive_link.features.inc
 */

/**
 * Implements hook_node_info().
 */
function features_content_type_drive_link_node_info() {
  $items = array(
    'drive_link' => array(
      'name' => t('Drive Link'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
