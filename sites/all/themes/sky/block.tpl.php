<?php
// $Id: block.tpl.php,v 1.1.4.1.4.1 2008/04/08 21:36:25 jgirlygirl Exp $
?>
<!-- start block.tpl.php -->
<div id="block-<?php print $block->module; ?>-<?php print $block->delta; ?>" class="block<?php print " block-$block->module"; ?>">
<?php if ($block->subject): ?>
  <div class="title"><?php print $block->subject; ?></div>
<?php endif; ?>
<?php if ($block->module == 'menu' || ($block->module == 'user' && $block->delta == 1) || ($block->module == 'book' && $block->delta == 0)) { ?>
  <div class="content-menu"><?php print $block->content; ?></div>
<?php }
else { ?>
  <div class="content"><?php print $block->content; ?></div>
<?php } ?>
</div>
<!-- start block.tpl.php -->