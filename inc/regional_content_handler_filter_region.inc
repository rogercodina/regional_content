<?php

/**
 * @file
 * Regional content handler filter.
 */

class regional_content_handler_filter_region extends views_handler_filter {

  function can_expose() { return TRUE; }

  /**
   * Implements views_object#admin_summary().
   */
  function admin_summary() {
    return '';
  }

  /**
   * Options form subform for setting exposed filter options.
   */
  function value_form(&$form, &$form_state) {
    parent::value_form($form, $form_state);

    $form['value']['user_region'] = array(
      '#type' => 'select',
      '#title' => '',
      '#options' => regional_content_get_all_regions_select(),
      '#default_value' => $category['selected'],
    );
  }

  /**
   * Alters Views query when filter is used.
   *
   * This ONLY gets executed if the filter IS NOT exposed. So check out functions
   * inside regional_content.views.inc for exposed filtering.
   */
  function query() {

    $region = regional_content_get_current_region();
    $global_lists_all = variable_get('regional_content_global_lists_all', 0);

    if (($global_lists_all == 0) || $region != variable_get('regional_content_global_tid')) {

      // Global region is not selected.
      if ( $this->query instanceof SearchApiViewsQuery ) {
        $this->query->condition('field_regional_content', $region, '=');
      }
      else {
        $join = new views_join();
        $join->table = 'field_data_field_regional_content';
        $join->field = 'entity_id';
        $join->left_table = 'node';
        $join->left_field = 'nid';
        $join->type = 'INNER';
        $join->extra = array(
          array(
            'field' => 'field_regional_content_target_id',
            'value' => $region,
          )
        );
        $this->query->add_relationship('field_data_field_regional_content', $join, 'node');
	    }
	  }
  }
}
