<?php
// $Id: taxonomy_breadcrumb.admin.inc,v 1.1.2.2 2009/04/24 02:51:41 mgn Exp $

/**
 * @file
 * Administration pages for taxonomy_breadcrumb
 */

/**
 * Settings page for module.
 */
function taxonomy_breadcrumb_admin_settings() {
  $form['settings'] = array(
    '#type'           => 'fieldset',
    '#title'          => t('Basic Settings'),
    '#collapsible'    => TRUE,
  );

  $form['settings']['taxonomy_breadcrumb_home'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Home breadcrumb text'),
    '#default_value'  => variable_get('taxonomy_breadcrumb_home', ''),
    '#description'    => t('Text to display at top of breadcrumb trail.  Typically home or your site name.  Leave blank to have no home breadcrumb.'),
  );

  $form['settings']['taxonomy_breadcrumb_show_current_term'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Show current term in breadcrumb trail?'),
    '#default_value'  => variable_get('taxonomy_breadcrumb_show_current_term', TRUE),
    '#description'    => t('When enabled, the lightest term associated with node is shown as the last breadcrumb in the breadcrumb trail.  When disabled, the only terms shown in the breadcrumb trail are parent terms (if any parents exist).  The recommended setting is enabled.'),
  );

  $form['settings']['taxonomy_breadcrumb_include_node_title'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Show current node title in breadcrumb trail?'),
    '#default_value'  => variable_get('taxonomy_breadcrumb_include_node_title', FALSE),
    '#description'    => t('When enabled and when viewing a node, the node\'s title will be shown as the last breadcrumb in the breadcrumb trail.'),
    '#weight'         => 30,
  );

  $form['advanced'] = array(
    '#type'           => 'fieldset',
    '#description'    => 'Use these advanced settings to control which node types taxonomy based breadcrumbs will be generated for.  This allows taxonomy_breadcrumb to peacefully coexist with modules that define their own breadcrumbs, such as the book module.  For typical drupal configurations, administrators will not need to modify these settings; however, if user contributed modules are enabled you may need to fine tune taxonomy_breadcrumb here.',
    '#title'          => t('Advanced Settings'),
    '#collapsible'    => TRUE,
    '#collapsed'      => TRUE,
  );

  $form['advanced']['taxonomy_breadcrumb_include_nodes'] = array(
    '#type'           => 'radios',
    '#title'          => t('Include or exclude the following node types'),
    '#default_value'  => variable_get('taxonomy_breadcrumb_include_nodes', FALSE),
    '#options'        => array(TRUE => t('Include'), FALSE => t('Exclude')),
    '#weight'         => 10,
  );

  $tb_types = (array) variable_get('taxonomy_breadcrumb_node_types', TAXONOMY_BREADCRUMB_NODE_TYPES_DEFAULT);
  $default = array();
  foreach ($tb_types as $index => $value) {
    if ($value) {
      $default[] = $index;
    }
  }

  $form['advanced']['taxonomy_breadcrumb_node_types'] = array(
    '#type'           => 'checkboxes',
    '#multiple'       => TRUE,
    '#title'          => t('Node types to include or exclude'),
    '#default_value'  => $default,
    '#options'        => array_map('check_plain', node_get_types('names')),
    '#description'    => t('A list of node types to include or exclude applying taxonomy based breadcrumbs to.'),
    '#weight'         => 20,
  );

  return system_settings_form($form);
}
