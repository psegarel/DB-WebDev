<?php
// $Id: videofield_widget.inc,v 1.10 2010/02/04 23:42:11 tamerzg Exp $

/**
 * @file
 * Videofield widget hooks and callbacks.
 */

/**
 * Implementation of CCK's hook_widget_settings($op = 'form').
 */
function videofield_widget_settings_form($widget) {
  $form = module_invoke('filefield', 'widget_settings', 'form', $widget);

  $video_types=_videofield_supported_filetypes();
 $form['file_extensions'] = array(
    '#type' => 'textfield',
    '#title' => t('Permitted upload file extensions'),
    '#default_value' => is_string($widget['file_extensions']) ? $widget['file_extensions'] :$video_types,
    '#size' => 64,
    '#description' => t('Extensions a user can upload to this field. Separate extensions with a space and do not include the leading dot. Leaving this blank will allow users to upload a file with any extension.'),
    '#weight' => 1,
  );

  return $form;
}



/**
 * Implementation of CCK's hook_widget_settings($op = 'save').
 */
function videofield_widget_settings_save($widget) {
  $filefield_settings = module_invoke('filefield', 'widget_settings', 'save', $widget);
   
  return $filefield_settings;
}

/**
 * Element #value_callback function.
 */
function videofield_widget_value($element, $edit = FALSE) {
  $field = filefield_widget_value($element, $edit);
 
  return $field;
}

/**
 * Element #process callback function.
 */
function videofield_widget_process($element, $edit, &$form_state, $form) {
  $file = $element['#value'];
  
  //Read width and height if it was already saved
  $width=$file['data']['width'];
  $height=$file['data']['height'];

  if(empty($width)){
   $width=variable_get('videofield_videowidth', 350);
  }
  if(empty($height)){
    $height=variable_get('videofield_videoheight', 285);
  }
  

  $field = content_fields($element['#field_name'], $element['#type_name']);

  $element['data']['width'] = array( 
    '#title' => t( 'Width' ),
    '#type' => 'textfield',
    '#default_value' =>$width,
  );
  $element['data']['height'] = array( 
    '#title' => t( 'Height' ),
    '#type' => 'textfield',
    '#default_value' => $height,
  );
  
  //TODO: Configuration for display. Make popup display.
  /*
  $default_display= $defaults['display'];
  if(!isset($default_display))
     $default_display=0;
     
  $element['data']['display'] = array( 
    '#title' => t( 'Display' ),
    '#type' => 'radios',
    '#default_value' => $default_display,
    '#options' => array(t('Embedded'), t('Popup')),
  );
*/

  return $element;
}


/**
 * FormAPI theme function. Theme the output of an image field.
 */
function theme_videofield_widget($element) {
  
  $z=theme('form_element', $element, $element['#children']);
  
  return $z;
}

function theme_videofield_widget_preview($item) {
  // Remove the current description so that we get the filename as the link.
  if (isset($item['data']['description'])) {
    unset($item['data']['description']);
  }

  return '<div class="videofield-file-info">'.
           '<div class="filename">'. theme('videofield_file', $item) .'</div>'.
           '<div class="filesize">'. format_size($item['filesize']) .'</div>'.
           '<div class="filemime">'. $item['filemime'] .'</div>'.
         '</div>';
}

function theme_videofield_widget_item($element) {
  return theme('filefield_widget_item', $element);
}

/**
 * Custom theme function for videofield upload elements.
 *
 * This function allows us to put the "Upload" button immediately after the
 * file upload field by respecting the #field_suffix property.
 */
function theme_videofield_widget_file($element) {
  $output = '';

  $output .= '<div class="videofield-upload clear-block">';

  if (isset($element['#field_prefix'])) {
    $output .= $element['#field_prefix'];
  }

  _form_set_class($element, array('form-file'));
  $output .= '<input type="file" name="'. $element['#name'] .'"'. ($element['#attributes'] ? ' '. drupal_attributes($element['#attributes']) : '') .' id="'. $element['#id'] .'" size="'. $element['#size'] ."\" />\n";

  if (isset($element['#field_suffix'])) {
    $output .= $element['#field_suffix'];
  }

  $output .= '</div>';

  return theme('form_element', $element, $output);
}

function _videofield_supported_filetypes(){

 $video_types = array(
      'mov', 'mp4', '3gp', '3g2', 'mpg', 'mpeg', // quicktime
      'divx', //divx
      'rm', // realplayer
      'flv', 'f4v', //flash player
      'swf', // swf player
      'dir', 'dcr', // dcr player
      'asf', 'wmv', 'avi', 'mpg', 'mpeg', // windows media
      'ogg' // ogg theora
  );
  $formatted_video_types=implode(' ', $video_types);
  return $formatted_video_types;
}