<?php

/**
 * @file
 * User login page - Template file.
 */
?>
<div id="auth_box" class="login magictime vanishIn">
  <div id="top_part">
    <h1 id="the_logo">
      <a href="<?php print url('<front>'); ?>">
        <img src="<?php print $logo; ?>" alt="<?php print $site_name; ?>">
      </a>
    </h1>
  </div>

  <div id="middle_part">
    <img src="/sites/all/themes/enorm/assets/img/logo-enorm.png" class="enorm-logo">
    <?php print $messages; ?>

    <?php print render($page['content']); ?>
  </div>

  <div id="bottom_part">
    <div class="password_link">
      <?php print l(t('Forgot your password?'), 'user/password'); ?>
    </div>
  </div>
</div>
