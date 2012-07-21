// $Id: user.js,v 1.6 2007/09/12 18:29:32 goba Exp $

/**
 * Attach handlers to check the password confirmation is correct.
 * Taken from modules/user/user.js
 */
Drupal.behaviors.password = function(context) {
  var translate = Drupal.settings.password;
  $("input.password-field:not(.password-processed)", context).each(function() {
    var passwordInput = $(this).addClass('password-processed');
    var parent = $(this).parent();
    // Wait this number of milliseconds before checking password.
    var monitorDelay = 700;

    // Add the password confirmation layer.
    var outerItem  = $(this).parent().parent();
    $("input.password-confirm", outerItem).after('<span class="password-confirm">'+ translate["confirmTitle"] +' <span></span></span>').parent().addClass("confirm-parent");
    var confirmInput = $("input.password-confirm", outerItem);
    var confirmResult = $("span.password-confirm", outerItem);
    var passwordStrength = $("span.password-strength", outerItem);
    var confirmChild = $("span", confirmResult);

    // Check the password fields.
    var passwordCheck = function () {
      // Remove timers for a delayed check if they exist.
      if (this.timer) {
        clearTimeout(this.timer);
      }

      // Check that password and confirmation match.

      // Hide the result layer if confirmation is empty, otherwise show the layer.
      confirmResult.css({ visibility: (confirmInput.val() == "" ? "hidden" : "visible") });

      var success = passwordInput.val() == confirmInput.val();

      // Remove the previous styling if any exists.
      if (this.confirmClass) {
        confirmChild.removeClass(this.confirmClass);
      }

      // Fill in the correct message and set the class accordingly.
      var confirmClass = success ? "ok" : "error";
      confirmChild.html(translate["confirm"+ (success ? "Success" : "Failure")]).addClass(confirmClass);
      this.confirmClass = confirmClass;
    };

    // Do a delayed check on the password fields.
    var passwordDelayedCheck = function() {
      // Postpone the check since the user is most likely still typing.
      if (this.timer) {
        clearTimeout(this.timer);
      }

      // When the user clears the field, hide the tips immediately.
      if (!passwordInput.val()) {
        passwordStrength.css({ visibility: "hidden" });
        passwordDescription.hide();
        return;
      }

      // Schedule the actual check.
      this.timer = setTimeout(passwordCheck, monitorDelay);
    };
    // Monitor keyup and blur events.
    // Blur must be used because a mouse paste does not trigger keyup.
    passwordInput.keyup(passwordDelayedCheck).blur(passwordCheck);
    confirmInput.keyup(passwordDelayedCheck).blur(passwordCheck);
  });
};
// $Id: user.js,v 1.6 2007/09/12 18:29:32 goba Exp $

/**
 * Attach handlers to check the password confirmation is correct.
 * Taken from modules/user/user.js
 */
Drupal.behaviors.password = function(context) {
  var translate = Drupal.settings.password;
  $("input.password-field:not(.password-processed)", context).each(function() {
    var passwordInput = $(this).addClass('password-processed');
    var parent = $(this).parent();
    // Wait this number of milliseconds before checking password.
    var monitorDelay = 700;

    // Add the password confirmation layer.
    var outerItem  = $(this).parent().parent();
    $("input.password-confirm", outerItem).after('<span class="password-confirm">'+ translate["confirmTitle"] +' <span></span></span>').parent().addClass("confirm-parent");
    var confirmInput = $("input.password-confirm", outerItem);
    var confirmResult = $("span.password-confirm", outerItem);
    var passwordStrength = $("span.password-strength", outerItem);
    var confirmChild = $("span", confirmResult);

    // Check the password fields.
    var passwordCheck = function () {
      // Remove timers for a delayed check if they exist.
      if (this.timer) {
        clearTimeout(this.timer);
      }

      // Check that password and confirmation match.

      // Hide the result layer if confirmation is empty, otherwise show the layer.
      confirmResult.css({ visibility: (confirmInput.val() == "" ? "hidden" : "visible") });

      var success = passwordInput.val() == confirmInput.val();

      // Remove the previous styling if any exists.
      if (this.confirmClass) {
        confirmChild.removeClass(this.confirmClass);
      }

      // Fill in the correct message and set the class accordingly.
      var confirmClass = success ? "ok" : "error";
      confirmChild.html(translate["confirm"+ (success ? "Success" : "Failure")]).addClass(confirmClass);
      this.confirmClass = confirmClass;
    };

    // Do a delayed check on the password fields.
    var passwordDelayedCheck = function() {
      // Postpone the check since the user is most likely still typing.
      if (this.timer) {
        clearTimeout(this.timer);
      }

      // When the user clears the field, hide the tips immediately.
      if (!passwordInput.val()) {
        passwordStrength.css({ visibility: "hidden" });
        passwordDescription.hide();
        return;
      }

      // Schedule the actual check.
      this.timer = setTimeout(passwordCheck, monitorDelay);
    };
    // Monitor keyup and blur events.
    // Blur must be used because a mouse paste does not trigger keyup.
    passwordInput.keyup(passwordDelayedCheck).blur(passwordCheck);
    confirmInput.keyup(passwordDelayedCheck).blur(passwordCheck);
  });
};
