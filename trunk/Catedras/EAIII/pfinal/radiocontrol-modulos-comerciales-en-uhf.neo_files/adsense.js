function google_ad_request_done(google_ads) {
	var s='';
	var i;
	var cssurl="adsense_slink";

	if (google_header=='true') {

		if (google_ads[0].type=="image") {
			s+='<a href=\"'+google_info.feedback_url+'\" style="color:fffff"><span class="contenido">Ads By Google</span></a>';
			s+='<div style="text-align:center;"><a href="'+google_ads[0].url+'" target="_blank" title="go to '+google_ads[0].visible_url+'" onmouseout="window.status=\'\'" onmouseover="window.status=\'go to '+google_ads[0].visible_url+'\';return true"><img border="0" src="'+google_ads[0].image_url+'"width="'+google_ads[0].image_width+'"height="'+google_ads[0].image_height+'"></a>';
			if (google_image_size=="300x250") {
				s+='<!-- begin standard tag - 300 x 250 - anuncios limpios: run-of-site - do not modify --><iframe frameborder="0" marginwidth="0" marginheight="0" scrolling="no" width="300" height="250" src="http://adserving.cpxinteractive.com/st?ad_type=iframe&amp;ad_size=300x250&amp;section=267023"></iframe><!-- end tag -->';
			}
			s+='</div>';
		} else {

			s+='<a href=\"'+google_info.feedback_url+'\" style="color:000000"><div><span class="contenido"><span class="contenido"><font size="2" color="E6E6E6">Ads By Google</font></span></span></div></a>';
			for (i=0; i<google_ads.length; ++i) {
				className=i%2!=1?' class="kieven"':' class="kiodd"';

				s+='<li'+className+'>';

				s+='<div><a href="'+google_ads[i].url+'"class="killer_titulo1" style="color:285EA8" onmouseout="window.status=\'\'" onmouseover="window.status=\'go to '+google_ads[i].visible_url+'\';return true"> <span class="">'+google_ads[i].line1+'</span></a><br /><div><span class="killer_texto"><span class="killer_texto" style="padding-bottom:25px;"><font size="2">'+google_ads[i].line2+'&nbsp;'+google_ads[i].line3+'</font></span></span> <a href="'+google_ads[i].url+'" onmouseout="window.status=\'\'" onmouseover="window.status=\'go to '+google_ads[i].visible_url+'\';return true" target="_blank"><span class="killer_slink">'+google_ads[i].visible_url+'</span></a></div></div>';
			}
		}

	} else {
		var s='';
		var i;

		if (google_ads.length==0) {
			if (google_image_size=="300x250") {
			} else {
			}
			document.write(s);
			return;
		}

		if (google_ads[0].type=="image") {
			s+='<a style="text-decoration:none;" href=\"'+google_info.feedback_url+'\" style="color:000000"><span class="contenido">Ads By Google</span></a>';
			s+='<div style="text-align:center;"><a href="'+google_ads[0].url+'" target="_blank" title="go to '+google_ads[0].visible_url+'" onmouseout="window.status=\'\'" onmouseover="window.status=\'go to '+google_ads[0].visible_url+'\';return true"><img border="0" src="'+google_ads[0].image_url+'"width="'+google_ads[0].image_width+'"height="'+google_ads[0].image_height+'"></a>';
			if (google_image_size=="300x250") {
				s+='<!-- begin standard tag - 300 x 250 - anuncios limpios: run-of-site - do not modify --><iframe frameborder="0" marginwidth="0" marginheight="0" scrolling="no" width="300" height="250" src="http://adserving.cpxinteractive.com/st?ad_type=iframe&amp;ad_size=300x250&amp;section=267023"></iframe><!-- end tag -->';
			}
			s+='</div>';
		} else {

			if (google_ads.length==1) {

				s+='<a style="text-decoration:none; color:033567;" href=\"'+google_info.feedback_url+'\"><div class="sponsor_name"><span class="contenido"><span class="contenido"><font size="2">Ads By Google</font></span></span></div></a>';

				s+='<div>';
				s+='<a href="'+google_ads[0].url+'" class="killer_titulo1" style="color:285EA8" onmouseout="window.status=\'\'" onmouseover="window.status=\'go to '+google_ads[0].visible_url+'\';return true" target="_blank"> <span>'+google_ads[0].line1+'</span></a><br /><div><span class="killer_texto"><span class="killer_texto" style="padding-bottom:25px;"><font size="2">'+google_ads[0].line2+'&nbsp;'+google_ads[0].line3+'</font></span></span> <a style="text-decoration:none;" href="'+google_ads[0].url+'" onmouseout="window.status=\'\'" onmouseover="window.status=\'go to '+google_ads[0].visible_url+'\';return true" target="_blank"><span class="killer_slink">'+google_ads[0].visible_url+'</span></a></div></div>';

			} else if (google_ads.length>1) {
			

				s+='<a style="text-decoration:none; color:033567;" href=\"'+google_info.feedback_url+'\"><div class="sponsor_name"><span class="contenido"><span class="contenido"><font size="2">Ads By Google</font></span></span></div></a>';
				for (i=0; i<google_ads.length; ++i) {
					className=i%2!=1?' class="kieven"':' class="kiodd"';

					s+='<div'+className+'>';
					s+='<a href="'+google_ads[i].url+'" class="killer_titulo1" style="color:285EA8" onmouseout="window.status=\'\'" onmouseover="window.status=\'go to '+google_ads[i].visible_url+'\';return true" target="_blank"> <span>'+google_ads[i].line1+'</span></a><br /><div><span class="killer_texto"><span class="killer_texto" style="padding-bottom:25px;"><font size="2">'+google_ads[i].line2+'&nbsp;'+google_ads[i].line3+'</font></span></span> <a style="text-decoration:none;" href="'+google_ads[i].url+'" onmouseout="window.status=\'\'" onmouseover="window.status=\'go to '+google_ads[i].visible_url+'\';return true" target="_blank"><br /><span class="killer_slink">'+google_ads[i].visible_url+'</span></a></div></div>';
				}
			}
		}
	}
	document.write(s);
	return;
}