<?php

/**
 * @file
 * features_view_my_file.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function features_view_my_file_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create drive_link content'.
  $permissions['create drive_link content'] = array(
    'name' => 'create drive_link content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any drive_link content'.
  $permissions['delete any drive_link content'] = array(
    'name' => 'delete any drive_link content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own drive_link content'.
  $permissions['delete own drive_link content'] = array(
    'name' => 'delete own drive_link content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any drive_link content'.
  $permissions['edit any drive_link content'] = array(
    'name' => 'edit any drive_link content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own drive_link content'.
  $permissions['edit own drive_link content'] = array(
    'name' => 'edit own drive_link content',
    'roles' => array(),
    'module' => 'node',
  );

  return $permissions;
}
