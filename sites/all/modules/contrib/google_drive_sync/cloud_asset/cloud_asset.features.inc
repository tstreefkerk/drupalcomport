<?php
/**
 * @file
 * cloud_asset.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cloud_asset_ctools_plugin_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function cloud_asset_node_info() {
  $items = array(
    'cloud_asset' => array(
      'name' => t('Cloud asset'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
