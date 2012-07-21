$(document).ready(function() {
	blocks_ad_on_top_hacks('#block-ad-382'); 	//send more id to change the ad to the top of the page
});

function getHeaderBannerEl() {
	var banner = $('#header-banner')[0];
	if (!banner) {
		banner = document.createElement('span');
		banner.id = 'header-banner';
		$('#header-inner')[0].appendChild(banner);
	}
	return banner;

}

function blocks_ad_on_top_hacks() {
	for (var i=0;i<arguments.length;i++) {
		block_ad_on_top_hacks(arguments[i]);
	}
}

function block_ad_on_top_hacks(block) {
	var ad = $(block)[0];
	if (ad) {
		var banner = getHeaderBannerEl();
		banner.appendChild(ad);		
	}
}

