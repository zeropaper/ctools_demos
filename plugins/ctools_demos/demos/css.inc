<?php

$plugin = array(
  'hook menu' => 'ctools_demos_css_menu',
  'description' => t('CSS aggregation, caching, filtering and compression tools.'),
);


function ctools_demos_css_ctools_demos_demos_render() {
  $output = '';
  
  ctools_include('css');
  
  
  $bloated_css = "
/* Here, the 'non-existing-property' should be removed */
.a-css-selector { non-existing-property: pony; }

/* This one is ok, shouldn't be changed */
.an-other-css-selector { background-color: lime; }";
  
  $output .= '<dt>'. t('Original') .'</dt><dd>'. ctools_demos_highlight($bloated_css, 'css') .'</dd>';
  
  
  $correct_css = ctools_css_filter($bloated_css, FALSE);
  $output .= '<dt>'. t('Corrected, uncompressed') .'</dt><dd>'. ctools_demos_highlight($correct_css, 'css') .'</dd>';
  
  
  $correct_compressed_css = ctools_css_filter($bloated_css, TRUE);
  $output .= '<dt>'. t('Corrected, compressed') .'</dt><dd>'. ctools_demos_highlight($correct_compressed_css, 'css') .'<dd>';
  
  $id = 'css-demos-'. rand(1, 1000);
  $filename = ctools_css_store($id, $bloated_css);
  $output .= '<dt>ctools_cache_store(\''. $id .'\');</dt><dd>'. t('The filename returned is %filename and this is its content: !content', array(
    '!content' => ctools_demos_highlight(file_get_contents($filename), 'css'),
    '%filename' => $filename
  )) .'<dd>';
  
  $exists = array(
    FALSE => t('The file has been removed.'),
    TRUE => t('The file is still here.'),
  );
  ctools_css_clear($id);
  $exists_bool = is_file($filename);
  $output .= '<dt>ctools_cache_clear(\''. $id .'\');</dt><dd>'. $exists[$exists_bool] .'<dd>';
  
  $output = '<dl>' .$output .'</dl>';
//  
//  $output = "". $output ."Some interesting methods too:<br/>
//ctools_css_store(\$id, \$css, \$filter = TRUE)<br/>
//ctools_css_retrieve(\$id)";
//  
  return $output;
}