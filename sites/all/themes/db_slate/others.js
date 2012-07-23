// JavaScript Document
(function() {
	function fix_email_validation_style() {
		var e = $('#email_validation');
		if (e.length) {
			var wrapper = e.parents('.block-wrapper');
			if (wrapper.length) {
				var top = wrapper.parent();
				top.css('background', 'none');
				top.append(e);
				wrapper.remove();
			}
		}
	}
		  
	$(function() {
		// fix email validation's style
		fix_email_validation_style();
	});
})();