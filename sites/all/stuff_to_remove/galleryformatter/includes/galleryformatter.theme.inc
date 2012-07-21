<?php
// $Id: galleryformatter.theme.inc,v 1.1.2.14 2010/05/28 10:16:02 manuelgarcia Exp $

/**
 * @file
 * Provides theme preprocess for the galleryformatter default formatter
 */

/**
 * Preprocess function for galleryformatter.tpl.php
 */
function template_preprocess_galleryformatter_formatter_galleryformatter_default(&$vars) {
  // grab the widget settings for for both image cache presets we will be using later
  $widget = galleryformatter_get_field_settings($vars['element']['#field_name'], $vars['element']['#type_name']);
  $thumb_preset = $widget['thumb_preset'];
  $slide_preset = $widget['slide_preset'];
  $style = $widget['style'];

  // ONLY do something if both of these presets are set for this field
  if (isset($thumb_preset) && ($thumb_preset !== '0') && isset($slide_preset) && ($slide_preset !== '0')) {
    $children = element_children($vars['element']);
    foreach ($children as $key) {
      // Check that we actualy have an image in each element
      if (!empty($vars['element'][$key]['#item']['fid'])) {
        $items[] = $vars['element'][$key]['#item'];
      }
    }
    $num_of_images = count($items);
    // Setup our arrays of variables for the template file to use
    foreach ($items as $id => $field) {
      // Grab and sanitize image information
      $description = check_plain($field['data']['description']);
      $title = check_plain($field['data']['title']);
      $filename = $field['filename'];
      $filepath = $field['filepath'];
      // prepare the unique hash id per image
      $slideset_id = $vars['element']['#field_name'] .'-'. $vars['element']['#node']->nid;
      $hash_id = 'slide-'. $id .'-'. $slideset_id;

      // Check if alt attribute is already set, if not use the filename as alt attribute
      $alt = (isset($field['data']['alt']) && !empty($field['data']['alt'])) ? check_plain($field['data']['alt']) : $filename;

      // prepare slides
      $slides[$id]['image'] = theme('imagecache', $slide_preset, $filepath, $alt, $title);
      $slides[$id]['title'] = $title;
      $slides[$id]['description'] = $description ;
      $slides[$id]['filepath'] = $filepath;
      $slides[$id]['hash_id'] = $hash_id;

      // link the slides to the original image if so configured
      $vars['link_to_full'] = $widget['link_to_full']; // let the tpl know if we are liking or not
      if ($widget['link_to_full'] == TRUE) {
        $vars['gallery_style'] = 'galleryformatter-view-full '; // give the gallery a class for themers to play with
        $link_attributes = array(
          'title' => $title,
        );
        // integration with other modules for jQuery modal windows
        if (module_exists('colorbox')) {
          $link_attributes['class'] .= ' colorbox';
          $link_attributes['rel'] = 'gallery-['. $slideset_id .']';
        }
        if (module_exists('thickbox')) {
          $link_attributes['class'] .= ' thickbox';
        }
        if (module_exists('shadowbox')) {
          $link_attributes['rel'] = 'shadowbox['.$slideset_id .']';
        }
        if (module_exists('lightbox2')) {
          $link_attributes['rel'] = 'lightbox['. $slideset_id .']';
        }
        // link the slide image and include the span for the icon
        $slides[$id]['image'] = l('<span class="galleryformatter-view-full" title="'. t('View the full image') .'">'. t('View the full image') .'</span>'. $slides[$id]['image'], $filepath, array('attributes' => $link_attributes, 'html' => TRUE,));
      } // END linking to original

      // setup thumbnail images
      if($num_of_images > 1) {
        $thumbs[$id]['image'] = theme('imagecache', $thumb_preset, $filepath, $alt, $title);
        $thumbs[$id]['hash_id'] = $hash_id;
      }
    }

    // insert into the variables for the template file
    $vars['gallery_thumbs'] = $thumbs;
    $vars['gallery_slides'] = $slides;

    // Get the images width and height for use by the template
    $image_path = $slides[0]['filepath']; // the first image will be used to get the dimensions of the gallery
    $slide_dimensions = galleryformatter_getimage_dimensions($slide_preset, $image_path);
    $vars['gallery_slide_height'] = $slide_dimensions['height'];
    $vars['gallery_slide_width'] = $slide_dimensions['width'];
    /**
     * @todo:
     * Give our js some settings maybe
     * Give users some options on click vs. hover?
     */
    /*
    $settings = array();
    $settings['galleryformatter']['settingname'] = 'settingvalue';
    drupal_add_js($settings, 'setting');
    */

    // add the necessary JS and CSS files
    $modulepath = drupal_get_path('module', 'galleryformatter');
    // and setup the thumbnails dimensions if we have more than one images
    if($num_of_images > 1) {
      $thumb_dimensions = galleryformatter_getimage_dimensions($thumb_preset, $image_path);
      $vars['gallery_thumb_height'] = $thumb_dimensions['height'];
      $vars['gallery_thumb_width'] = $thumb_dimensions['width'];

      drupal_add_js($modulepath .'/theme/infiniteCarousel.js');
      drupal_add_js($modulepath .'/theme/galleryformatter.js');
    }
    // setup the style class
    $vars['gallery_style'] .= 'galleryformatter-'. drupal_strtolower($style);
    galleryformatter_add_css($style);
  }

  // account for any preset not selected and provide a link to configure them
  else {
    $destination = drupal_get_destination();
    $configure_path = 'admin/content/node-type/'. str_replace('_','-',$vars['element']['#type_name']) .'/fields/'. $vars['element']['#field_name'];
    $configure_link = l($vars['element']['#field_name'], $configure_path, (array('query' => $destination)));
    drupal_set_message('Please select both a thumbnail and slide presets in your Gallery Formatter settings for '. $configure_link .'. The jQuery gallery needs these settings to work.', 'warning');
  }
}
