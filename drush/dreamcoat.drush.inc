<?php

/**
 * @file
 *   drush integration for dreamcoat.
 */

/**
 * Implements hook_drush_command().
 *
 * @return array
 *   An associative array describing your command(s).
 */
function dreamcoat_drush_command() {
  $items = array();

  $items['solr-mark'] = array(
    'callback' => 'dreamcoat_drush_solr_mark_for_reindex',
    'description' => dt('Marks bundles for reindexing.'),
    'options' => array(
      'environment-id' => 'The environment ID',
    ),
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'
 *
 * @param string $section
 *   A string with the help section (prepend with 'drush:')
 *
 * @return string
 *   A string with the help text for your command.
 */
function dreamcoat_drush_help($section) {
  switch ($section) {
    case 'drush:solr-mark':
      return dt("This is a different approach to solr-mark-all from the apache solr module."
        . "\nUnlike the apachesolr command 'solr-mark-all', this allows you to mark bundles (content-types), and not entities.");
  }
  return '';
}

/**
 * Mark all of a specific environment id for reindexing
 */
function dreamcoat_drush_solr_mark_for_reindex() {
  $env_id =  drush_get_option('environment-id');
  if (empty($env_id)) {
    $env_id = apachesolr_default_environment();
  }
  $info = entity_get_info('node');
  $bundles = $info['bundles'];
  $options = array();
  foreach ($bundles as $type => $bundle) {
    if ($bundle['apachesolr']['index'] === true) {
      $options[$type] = $bundle['label'];
    }
  }
  $choice = drush_choice($options, dt('Which content type do you want to re-index?'));
  if ($choice) {
    module_load_include('inc', 'apachesolr', 'apachesolr.index');
    drush_print(dt('Marking @choice for re-index.', array('@choice' => $options[$choice])));
    apachesolr_index_node_solr_reindex($env_id, $choice);
    drush_print(dt('Finished marking @choice.', array('@choice' => $options[$choice])));
  } else {
    drush_user_abort();
  }
}

/**
 * Prototype: Mark all Content as indexed.
 *  @internal - not for use yet.
 */
function dreamcoat_drush_solr_unqueue() {
  $env_id = apachesolr_default_environment();
  apachesolr_environment_variable_set($env_id, 'apachesolr_index_last', array());
  $last_index = apachesolr_get_last_index_position($env_id, 'node');
  kpr($last_index);
//  $last_entity_id = 4517; @todo - find last entity_id.
//  $last_changed = 1400698828; @todo - add last changed.
  apachesolr_set_last_index_position($env_id, 'node', $last_changed, $last_entity_id);
  $env = apachesolr_environment_load($env_id);
  kpr($env);
  exit();
}
