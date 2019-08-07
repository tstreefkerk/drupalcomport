<?php

/**
 * @file
 * Node poup module views hooks.
 */

/**
 * Implements hook_views_data().
 */
function npop_views_data_alter(&$views_data) {
  // We are going to override our views_handler_field_node.
  // This we we can provide extra options for nodes to
  // have the linked content displayed inside a popup window.
  $views_data['node']['nid']['field']['handler'] = 'npop_handler_field_npop';
  $views_data['node']['title']['field']['handler'] = 'npop_handler_field_npop';
  $views_data['views_entity_node']['view_node']['field']['handler'] = 'npop_handler_field_npop_link';
}
