<?php
// $Id$ 

/**
 * Dynamic display block module template: vsd-highlight-50l-S - pager template
 * (c) Copyright Phelsa Information Technology 2009 - 2010. All rights reserved.
 * Version 1.0(15-MAR-2010) 
 * Licenced under GPL license
 * http://www.gnu.org/licenses/gpl.html
 */

/**
 * @file
 * Dynamic display block module template: vsd-highlight-50l-S - pager template
 * - Custom pager with images and text
 *
 * Available variables:
 * - $settings['delta']: Block number of the block.
 * - $settings['pager']: Type of pager to add
 * - $settings['pager2']: Add prev/next pager
 * - $settings['pager2_position']: position of the prev/next slider (slide and pager) 
 * - $settings['pager2_slide_prev']: text of prev pager item
 * - $settings['pager2_slide_next']: text of next pager item
 * - $views_slideshow_ddblock_pager_items: array with pager_items
 *
 * notes: don't change the ID names, they are used by the jQuery script.
 */
 $settings = $views_slideshow_ddblock_pager_settings;
// $settings['pager_position'] = 'left';

 $number_of_items = $settings['nr_of_items'];        // total number of items to show 
 $number_of_items_per_row=1;  // number of items to show in a row
?>
<!-- prev/next pager on slide -->
<?php if ($settings['pager2'] == 1 && $settings['pager2_position']['slide'] === 'slide'): ?>
 <div class="views-slideshow-ddblock-prev-next-slide views-slideshow-ddblock-prev-next-slide-<?php print $settings['pager_position'] ?>">
  <div class="prev-container">
   <a class="prev" href="#"><?php print $settings['pager2_slide_prev']?></a>
  </div>
  <div class="next-container">
   <a class="next" href="#"><?php print $settings['pager2_slide_next'] ?></a>
  </div>
 </div>
<?php endif; ?>

<div id="views-slideshow-ddblock-custom-pager-<?php print $settings['delta'] ?>" class="<?php print $settings['pager'] ?> <?php print $settings['pager'] ?>-<?php print $settings['pager_position'] ?> clear-block border">
 <div class="<?php print $settings['pager'] ?>-inner clear-block border">
  <?php if ($views_slideshow_ddblock_pager_items): ?>
   <?php $item_counter=0; ?>
   <?php foreach ($views_slideshow_ddblock_pager_items as $pager_item): ?>
    <div class="<?php print $settings['pager'] ?>-item <?php print $settings['pager'] ?>-item-<?php print $item_counter ?>">
     <div class="<?php print $settings['pager'] ?>-item-inner"> 
      <a href="#" title="navigate to topic" class="pager-link"><?php print $pager_item['pager_image']; ?><div class="<?php print $settings['pager'] ?>-item-text"><p><?php print $pager_item['pager_text']; ?></p></div></a>
     </div>
    </div> <!-- /custom-pager-item -->
    <?php $item_counter++;?>
     <?php if ($item_counter <> $number_of_items): ?>
       <div class="spacer-horizontal"><b></b></div>
     <?php endif; ?>  
   <?php endforeach; ?>
  <?php endif; ?>
 </div> <!-- /pager-inner-->
</div>  <!-- /pager-->


