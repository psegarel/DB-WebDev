// JavaScript Document
	$(document).ready(function() {
		blocks_ad_on_top_hacks('#block-ad-382'); 	//send more id to change the ad to the top of the page
		flash_above_ad_hacks();		//send more id to change the flash to be transparent(can put the menu above the flash)
	});
	
	
	

	function blocks_ad_on_top_hacks() {
		for (var i=0;i<arguments.length;i++) {
			block_ad_on_top_hacks(arguments[i]);
		}
	}
	
	function block_ad_on_top_hacks(block) {
		var ad = $(block)[0];
		if (ad) {
			var banner = $('#header .banner')[0];
			banner.appendChild(ad);
			ad.style.position = "relative";
			ad.style.left = "0px";
			ad.style.top = "0px";
		}
	}

	
		
	
	function flash_above_ad_hacks() {
		for (var i = 0;i<arguments.length;i++) {
			var fid = arguments[i];
			var flash_obj = $('#' + fid + ' object')[0];
			if (flash_obj) {
				var param = document.createElement('param');
				param.name = 'wmode';				
				param.value = 'transparent';
				flash_obj.appendChild(param);
			}
		}
	}