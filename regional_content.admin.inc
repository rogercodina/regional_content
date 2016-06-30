<?php

/**
 * @file
 * Administration page.
 */

/**
 * Configuration form.
 */
function regional_content_admin_settings($form, &$form_state) {

  $form['regions'] = array(
    '#type' => 'item',
    '#title' => '',
    '#markup'=> '<a target="_blank" href="/admin/structure/taxonomy/regional_content_reg">' . t('Configure regions and countries') . '</a>',
  );

  $form['regional_content_global_lists_all'] = array(
    '#type' => 'checkbox',
    '#title' => t('Global region lists everything'),
    '#default_value' => variable_get('regional_content_global_lists_all', 0),
    '#description' => t('When GLOBAL region is selected by user: If this is checked, all content is listed. If this is unchecked, only content with GLOBAL taxonomy term assigned will be listed.'),
  );

  return system_settings_form($form);
}
