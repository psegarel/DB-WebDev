<div class="<?php print $is_forum ? 'forum-reply-form ' : ''; ?>box">
  <?php if ($title): ?>
  <span class="title"><?php print $title; ?></span>
  <?php endif; ?>
  <?php print $content; ?>
</div>