(function($){
	$(document).ready(function(){
	
		var imagePath = "static/images/brain-boxing.jpg";
		$(".banner-image").backstretch(imagePath);

		// Fixed header
		//-----------------------------------------------
		$(window).scroll(function() {
			if (($(".header.fixed").length > 0)) { 
				if(($(this).scrollTop() > 0) && ($(window).width() > 767)) {
					$("body").addClass("fixed-header-on");
				} else {
					$("body").removeClass("fixed-header-on");
				}
			};
		});

		$(window).load(function() {
			if (($(".header.fixed").length > 0)) { 
				if(($(this).scrollTop() > 0) && ($(window).width() > 767)) {
					$("body").addClass("fixed-header-on");
				} else {
					$("body").removeClass("fixed-header-on");
				}
			};
		});
		
	   $('#quote-carousel').carousel({
		 pause: true,
		 interval: 4000,
	   });
		//Scroll Spy
		//-----------------------------------------------
		if($(".scrollspy").length>0) {
			$("body").addClass("scroll-spy");
			$('body').scrollspy({ 
				target: '.scrollspy',
				offset: 152
			});
		}

		//Smooth Scroll
		//-----------------------------------------------
		if ($(".smooth-scroll").length>0) {
			$('.smooth-scroll a[href*=#]:not([href=#]), a[href*=#]:not([href=#]).smooth-scroll').click(function() {
				if (location.pathname.replace(/^\//,'') == this.pathname.replace(/^\//,'') && location.hostname == this.hostname) {
					var target = $(this.hash);
					target = target.length ? target : $('[name=' + this.hash.slice(1) +']');
					if (target.length) {
						$('html,body').animate({
							scrollTop: target.offset().top-151
						}, 1000);
						return false;
					}
				}
			});
		}

		// Animations
		//-----------------------------------------------
		if (($("[data-animation-effect]").length>0) && !Modernizr.touch) {
			$("[data-animation-effect]").each(function() {
				var $this = $(this),
				animationEffect = $this.attr("data-animation-effect");
				if(Modernizr.mq('only all and (min-width: 768px)') && Modernizr.csstransitions) {
					$this.appear(function() {
						setTimeout(function() {
							$this.addClass('animated object-visible ' + animationEffect);
						}, 400);
					}, {accX: 0, accY: -130});
				} else {
					$this.addClass('object-visible');
				}
			});
		};

		// Like and love buttons - start
		let like = parseInt(document.querySelector('#score_like').innerHTML);
		let love = parseInt(document.querySelector('#score_love').innerHTML);
	
		document.querySelector('#add_like').onclick = function() {
			like += 1;
			document.querySelector('#score_like').innerHTML = like;
			updateLikeInDatabase(like);
		}
	
		document.querySelector('#add_love').onclick = function() {
			love += 1;
			document.querySelector('#score_love').innerHTML = love;
			updateLoveInDatabase(love);
		}

		function updateLikeInDatabase(newLike) {
			$.ajax({
				type: 'POST',
				url: '/update_like',
				data: JSON.stringify({ like: newLike }),
				contentType: 'application/json',
				success: function(response) {
					console.log('Like updated in the database');
				}
			});
		}

		function updateLoveInDatabase(newLove) {
            $.ajax({
                type: 'POST',
                url: '/update_love',
                data: JSON.stringify({ love: newLove }),
                contentType: 'application/json',
                success: function(response) {
                    console.log('Love updated in the database');
                }
            });
        }
		// Like and love buttons - end

	}); // End document ready
})(this.jQuery);
