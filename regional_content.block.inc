<?php

/**
 * Block visibility logic, based on i18n_block module.
 */

/**
 * Implements block hook_form_FORM_ID_alter().
 *
 * Add region visibility options to blocks (creation form).
 */
function regional_content_form_block_add_block_form_alter(&$form, &$form_state, $form_id) {
  regional_content_form_block_admin_configure_alter($form, $form_state, $form_id);
}

/**
 * Implements block hook_form_FORM_ID_alter().
 *
 * Add region visibility options to blocks (edition form).
 */
function regional_content_form_block_admin_configure_alter(&$form, &$form_state, $form_id) {
  $form['regional_content']['regions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Regions'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'visibility',
    '#weight' => 6,
  );

  // Add option to select which region blocks to show on.
  $default_options = db_query("SELECT region FROM {regional_content_region} WHERE module = :module AND delta = :delta", array(
    ':module' => $form['module']['#value'],
    ':delta' => $form['delta']['#value'],
  ))->fetchCol();

  $form['regional_content']['regions']['custom_regions'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Show this block for these regions'),
    '#default_value' => $default_options,
    '#options' => regional_content_get_all_regions_select(false),
    '#description' => t('If no region is selected, block will show regardless of region.'),
  );

  $form['#submit'][] = 'regional_content_form_block_admin_configure_submit';
}

/**
 * Form submit handler for block configuration form.
 *
 * @see regional_content_form_block_admin_configure_alter()
 */
function regional_content_form_block_admin_configure_submit(&$form, &$form_state) {
  $module = $form_state['values']['module'];
  $delta = $form_state['values']['delta'];

  // Update block regions
  db_delete('regional_content_region')
    ->condition('module', $module)
    ->condition('delta', $delta)
    ->execute();
  $query = db_insert('regional_content_region')->fields(array('region', 'module', 'delta'));

  foreach (array_filter($form_state['values']['custom_regions']) as $region) {
    $query->values(array(
      'region' => $region,
      'module' => $module,
      'delta' => $delta,
    ));
  }
  $query->execute();
}

/**
 * Implements hook_block_list_alter().
 *
 * To be run after all block visibility modules have run, just hide the blocks given region.
 */
function regional_content_block_list_alter(&$blocks) {
  global $theme_key;
  $current_region = regional_content_get_current_region();

  // Build an array of node types for each block.
  $block_regions = array();
  $result = db_query('SELECT module, delta, region FROM {regional_content_region}');
  foreach ($result as $record) {
    $block_regions[$record->module][$record->delta][$record->region] = TRUE;
  }

  foreach ($blocks as $key => $block) {
    if (!isset($block->theme) || !isset($block->status) || $block->theme != $theme_key || $block->status != 1) {
      // This block was added by a contrib module, leave it in the list.
      continue;
    }
    if (isset($block_regions[$block->module][$block->delta]) && !isset($block_regions[$block->module][$block->delta][$current_region])) {
      // Block not visible for this region.
      unset($blocks[$key]);
    }
  }
}

/**
 * Implements hook_form_FORMID_alter().
 *
 * Adds node specific submit handler to delete custom block form.
 *
 * @see block_custom_block_delete()
 */
function regional_content_form_block_custom_block_delete_alter(&$form, &$form_state) {
  $form['#submit'][] = 'regional_content_form_block_custom_block_delete_submit';
}

/**
 * Form submit handler for custom block delete form.
 */
function regional_content_form_block_custom_block_delete_submit($form, &$form_state) {
  db_delete('regional_content_region')
    ->condition('module', 'block')
    ->condition('delta', $form_state['values']['bid'])
    ->execute();
}
