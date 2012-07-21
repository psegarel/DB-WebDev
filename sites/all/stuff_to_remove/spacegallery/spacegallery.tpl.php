<?php  // $Id: spacegallery.tpl.php,v 1.1 2010/03/12 21:04:37 rashad612 Exp $
?>
<div id="space-gallery" class="spacegallery">
  <?php foreach($rows as $row): ?>
    <div class="spacegallery-item"><?php print $row; ?></div>
  <?php endforeach; ?>
</div>
