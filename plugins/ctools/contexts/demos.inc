<?php
$plugin = array(
  'context' => 'ctools_demos_context_demos',
  'context name' => 'demos',
  'title' => t('CTools Demos context'),
  'description' => t('CTools Demos context'),
  // a keyword to use for substitution in titles, used in Panels
  'keyword' => 'demos',
  
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter some data to represent this "demos".'),
  ),
  
  'defaults' => array(
    'current' => 'ajax'
  ),
  
  'settings form' => 'demos_settings_form',
  
  // 'context name' => 'demos',
  // 'no ui' => TRUE,
  // 'settings form validate' => 'ctools_demos_context_settings_validate',
  // 'settings form submit' => 'ctools_demos_context_settings_submit',
);


/**
 * It's important to remember that $conf is optional here, because contexts
 * are not always created from the UI.
 */
function ctools_demos_context_demos($empty, $data = NULL, $conf = FALSE) {
  $context = new ctools_context('demos');
  $context->plugin = 'demos';
  
  if ($empty) {
    return $context;
  }
  
  

  if ($conf) {
    if (!empty($data)) {
      // For this simple item we'll just create our data by stripping non-alpha and
      // adding '_from_configuration_item_1' to it.
      $context->data = new stdClass();
      $context->data->item1 = t("Item1");
      $context->data->item2 = t("Item2");
      $context->data->description = preg_replace('/[^a-z]/i', '', $data['sample_demos_setting']);
      $context->data->description .= '_from_configuration_sample_demos_setting';
      $context->title = t("Simplecontext context from config");
      return $context;
    }
  }
  else {
    // $data is coming from an arg - it's just a string.
    // This is used for keyword.
    $context->title = $data;
    $context->argument = $data;
    // Make up a bogus context
    
    // For this simple item we'll just create our data by stripping non-alpha and
    // adding '_from_demos_argument' to it.
    $context->data = new stdClass();
    $context->data->item1 = t("Item1");
    $context->data->item2 = t("Item2");
    $context->data->description = preg_replace('/[^a-z]/i', '', $data);
    $context->data->description .= '_from_demos_argument';
    $context->arg_length = strlen($context->argument);
    return $context;
  }
}


function demos_settings_form($conf, $external = FALSE) {
  if (empty($conf)) {
    $conf = array(
      'sample_demos_setting' => 'default demos setting',
    );
  }
  $form = array();
  $form['sample_demos_setting'] = array(
    '#type' => 'textfield',
    '#title' => t('Setting for demos'),
    '#size' => 50,
    '#description' => t('An example setting that could be used to configure a context'),
    '#default_value' => $conf['sample_demos_setting'],
    '#prefix' => '<div class="clear-block no-float">',
    '#suffix' => '</div>',
  );
  return $form;
}



/**
 * Provide a list of sub-keywords.
 *
 * This is used to provide keywords from the context for use in a content type,
 * pane, etc.
 */
function demos_convert_list() {
  return array(
    'item1' => t('Item1'),
    'item2' => t('Item2'),
    'description' => t('Description'),
  );
}

/**
 * Convert a context into a string to be used as a keyword by content types, etc.
 */
function demos_convert($context, $type) {
  switch ($type) {
    case 'item1':
      return $context->data->item1;
    case 'item2':
      return $context->data->item2;
    case 'description':
      return $context->data->description;
  }
}