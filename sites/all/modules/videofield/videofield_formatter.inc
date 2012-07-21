<?php
//$Id: videofield_formatter.inc,v 1.12 2009/11/28 11:08:52 tamerzg Exp $
/**
 * @file
 * videofield_formatter
 *
 * @author Tamer Al Zoubi [tamerzg@gmail.com]
 * @author Heshan Wanigasooriya <heshan at heidisoft dot com><heshanmw at gmail dot com>
 * @TODO adding other player functions
 */

/**
* Theme function for 'embedded' video.
*/
function theme_videofield_formatter_videofield_embedded($element) {
  //include the cmmon.inc file
  module_load_include('inc', 'videofield', 'common');
  
  //Don't render player if there is no file.
  if (!$element['#item']['filepath']) {
    return '';
  }

  return _video_field_common_get_player($element);
}

/* 
 * Theme function for popup videofield field formatter. 
 */
function theme_videofield_formatter_videofield_popup($element) {
  
  return $output;
}

/**
 * Theme function for any file that is managed by FileField.
 *
 * It doesn't really format stuff by itself but rather redirects to other
 * formatters that are telling us they want to handle the concerned file.
 *
 * This function checks if the file may be shown and returns an empty string
 * if viewing the file is not allowed for any reason. If you need to display it
 * in any case, please use theme('filefield') instead.
 */
function theme_videofield_item($file, $field) {
  if (filefield_view_access($field['field_name']) && filefield_file_listed($file, $field)) {
    return theme('filefield_file', $file);
  }
  return '';
}

/**
 * Theme function for the 'generic' single file formatter.
 */
function theme_videofield_file($file) {
  // Views may call this function with a NULL value, return an empty string.
  if (empty($file['fid'])) {
    return '';
  }

  $path = $file['filepath'];
  $url = file_create_url($path);
  $icon = theme('filefield_icon', $file);

  // Set options as per anchor format described at
  // http://microformats.org/wiki/file-format-examples
  // TODO: Possibly move to until I move to the more complex format described 
  // at http://darrelopry.com/story/microformats-and-media-rfc-if-you-js-or-css
  $options = array(
    'attributes' => array(
      'type' => $file['filemime'] . '; length=' . $file['filesize'],
    ),
  );

  // Use the description as the link text if available.
  if (empty($file['data']['description'])) {
    $link_text = $file['filename'];
  }
  else {
    $link_text = $file['data']['description'];
    $options['attributes']['title'] = $file['filename'];
  }

  return '<div class="filefield-file clear-block">'. $icon . l($link_text, $url, $options) .'</div>';
}
