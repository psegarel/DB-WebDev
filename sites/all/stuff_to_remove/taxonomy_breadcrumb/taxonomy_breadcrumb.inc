<?php
// $Id: taxonomy_breadcrumb.inc,v 1.1.2.3 2009/05/31 19:37:18 mgn Exp $

/**
 * @file
 * helper functions for taxonomy_breadcrumb
 */

/**
 * This function overrides the core taxonomy_term_page.  First, call the core
 * taxonomy_term_page.  Then, alter the breadcrumb trail.  This module's
 * hook_menu and a module weight greater than taxonomy's ensure this
 * function gets called for the taxonomy/term path (the module weight is
 * in the system table and is set in taxonomy_breadcrumb.install).
 */
function _taxonomy_breadcrumb_term_page($str_tids = '', $depth = 0, $op = 'page') {
  static $callback = array();
  if (empty($callback)) {
    $callback = variable_get('taxonomy_breadcrumb_override_callback', array() );
    if (!empty($callback)) {
      $require_path = isset($callback['file path']) ? $callback['file path'] : drupal_get_path('module', $callback['module']);
      require_once($require_path .'/'. $callback['file']);
    }
    else {
      // Default to core taxonomy_term_page callback.
      // Include the .inc file with all helper functions.
      require_once(drupal_get_path('module', 'taxonomy') .'/taxonomy.pages.inc');
    }
  }
  if (isset($callback['page callback'])) {
    $func = $callback['page callback'];
    // Assume that any function overriding the core taxonomy function would have the same parameters.
    $output = $func($str_tids, $depth, $op);
  }
  else {
    // Call the core taxonomy_term_page function.
    $output = taxonomy_term_page($str_tids, $depth, $op);
  }

  // Use first term to generate breadcrumb trail.
  $terms = taxonomy_terms_parse_string($str_tids);
  $breadcrumb = _taxonomy_breadcrumb_generate_breadcrumb($terms['tids'][0], TRUE);
  drupal_set_breadcrumb($breadcrumb);
  return $output;
}

/**
 * Return lightest term for given node ($nid).
 * Similar to taxonomy_node_get_terms, but only return the lightest term in the
 * lightest vocab for the node.
 */
function _taxonomy_breadcrumb_node_get_lightest_term($nid) {

  // We only want the first row of the result. This is the lightest term of the
  // lightest vocab.
  $result = db_query(db_rewrite_sql('SELECT t.* FROM {term_node} r INNER JOIN {term_data} t ON r.tid = t.tid INNER JOIN {term_hierarchy} h ON t.tid = h.tid INNER JOIN {vocabulary} v ON t.vid = v.vid WHERE r.nid = %d ORDER BY v.weight, h.parent DESC, t.weight, t.name', 't', 'tid'), $nid);

  // Extract the first row of query.
  $term = db_fetch_object($result);

  return $term;
}

/**
 * Return the administrator defined vocabulary path for a given vocabulary
 * ($vid).  If a path doesn't exist, NULL is returned.
 */
function _taxonomy_breadcrumb_get_vocabulary_path($vid) {
  $result = db_query("SELECT path FROM {taxonomy_breadcrumb_vocabulary} WHERE vid = %d", $vid);
  $path = NULL;
  if ($row = db_fetch_array($result)) {
    $path = $row['path'];
  }
  return $path;
}

/**
 * Return the administrator defined term path for a given term ($tid).
 * If a path doesn't exist, NULL is returned.
 */
function _taxonomy_breadcrumb_get_term_path($tid) {
  $result = db_query("SELECT path FROM {taxonomy_breadcrumb_term} WHERE tid = %d", $tid);
  $path = NULL;
  if ($row = db_fetch_array($result)) {
    $path = $row['path'];
  }
  return $path;
}

/**
 * If the current drupal path (q=) is /node/nid, generate the breadcrumb trail
 * based on nid.
 */
function _taxonomy_breadcrumb_generate_breadcrumb($tid, $is_term_page = FALSE) {

  $term = taxonomy_get_term($tid);

  // Generate the HOME breadcrumb.
  $home_text = variable_get('taxonomy_breadcrumb_home', '');
  if ($home_text != '') {
    $breadcrumb[] = l(t($home_text), NULL);
  }
  // Generate the VOCABULARY breadcrumb.
  $vocabulary_path = _taxonomy_breadcrumb_get_vocabulary_path($term->vid);
  if ($vocabulary_path != NULL) {
    $vocabulary = taxonomy_vocabulary_load($term->vid);
    $breadcrumb[] = l(_taxonomy_breadcrumb_tt("taxonomy:vocabulary:$term->tid:name", $vocabulary->name), $vocabulary_path);
  }

  // Generate the TERM breadcrumb.
  $parent_terms = array_reverse(taxonomy_get_parents_all($tid));
  foreach ($parent_terms as $parent_term) {
    $term_path = _taxonomy_breadcrumb_get_term_path($parent_term->tid);
    if ($term_path == NULL) {
      $term_path = taxonomy_term_path(taxonomy_get_term($parent_term->tid));
    }
    // Do not create links to own self if we are on a taxonomy/term page.
    if ($is_term_page && $parent_term->tid == $tid) {
      $breadcrumb[] = _taxonomy_breadcrumb_tt("taxonomy:term:$parent_term->tid:name", $parent_term->name);
    }
    else {
      $breadcrumb[] = l(_taxonomy_breadcrumb_tt("taxonomy:term:$parent_term->tid:name", $parent_term->name), $term_path);
    }
  }

  // Optionally remove the current TERM from end of breadcrumb trail.
  if (!variable_get('taxonomy_breadcrumb_show_current_term', TRUE) && !is_null($breadcrumb)) {
      array_pop($breadcrumb);
  }
  return $breadcrumb;
}

/**
 * Helper function for when i18ntaxonomy module is not installed.
 */

function _taxonomy_breadcrumb_tt($string_id, $default, $language = NULL) {
  return function_exists('tt') ? tt($string_id, $default, $language) : $default;
}
