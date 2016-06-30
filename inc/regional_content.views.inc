<?php

/**
 * @file
 * Views integration.
 */

/**
 * Implements hook_views_query_alter().
 *
 * Only way to modify the query if the filter IS exposed.
 */
function regional_content_views_query_alter(&$view, &$query) {
  $region = !empty($view->exposed_raw_input) ? $view->exposed_raw_input['user_region'] : '';
  $global_lists_all = variable_get('regional_content_global_lists_all', 0);

  if (!empty($region) && (($global_lists_all == 0) || $region != variable_get('regional_content_global_tid')) ) {

    // Global region is not selected.
    $query->add_where_expression(1, "field_regional_content_target_id = :tid ", array(':tid' => $region));
    $query->add_table('field_data_field_regional_content');
    //dpm($query);
  }
}


/**
 * Implements hook_search_api_views_query_alter().
 *
 * Only way to modify the query if the filter IS exposed.
 * This function only gets executed on Search API views.
 */
function regional_content_search_api_views_query_alter(&$view, &$query) {
  $region = !empty($view->exposed_raw_input) ? $view->exposed_raw_input['user_region'] : '';
  $global_lists_all = variable_get('regional_content_global_lists_all', 0);

  if (!empty($region) && (($global_lists_all == 0) || $region != variable_get('regional_content_global_tid')) ) {

    // Global region is not selected.
    $main_filter = $query->createFilter('AND');
    $main_filter->condition('field_regional_content', $region, '=');
    $query->filter($main_filter);
    //dpm($query);
  }
}
