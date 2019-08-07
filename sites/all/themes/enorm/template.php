<?php

/**
 * @file
 * Bootstrap sub-theme.
 *
 * Place your custom PHP code in this file.
 */

function enorm_theme($existing, $type, $theme, $path) {
    $items['enorm_company_search_form'] = array(
        'render element' => 'form',
        'template' => 'company-search',
        'path' => drupal_get_path('theme', 'enorm') . '/templates/form',
    );

    return $items;
}

/**
 * Implements hook_form().
 */
function enorm_company_search_form($node, &$form_state)
{
    $form['name'] = array(
        '#title' => t("Company ID search"),
        '#type' => 'textfield',
        '#required' => TRUE,
    );

    // Provide a submit button.
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => 'Search',
    );

    return $form;
}


