<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 23/04/14
 * Time: 20:48
 */

namespace Resources\Themes;

//Include debugging helper class
require_once('Utils/Debug/DbgHelper.inc');
use \Utils\Debug\DbgHelper as DbgHelper;

//Include configuration data
include_once('Resources/Config/cfg.inc');
use Resources\Config\Cfg as Cfg;

//Include localised string resources
require_once('Apps/' . Cfg::$appTitle . '/Resources/Strings/' . Cfg::$locale . '.inc');
use Resources\Strings\Locale as Locale;

//Include global controller
require_once('Apps/' . Cfg::$appTitle . '/Controllers/CommonController.inc');
use \Controllers\CommonController as CommonController;

//Include base theme class
require_once('Resources/Themes/ThemeBase.inc');

//Check if the correct theme is loaded
if(strcmp(Cfg::$appTheme, "Materna") == 0)
{
    class Theme extends ThemeBase {
	    public static function GuiBeginDraw()
	    {
		    $head = "
			    <script src=\"http://code.jquery.com/jquery-latest.min.js\" type=\"text/javascript\"></script>
			    <script type=\"text/javascript\">
				    $(function(){
					    // Check the initial Position of the Sticky Header
					    var stickyHeaderTopLinks = $('#top-links').offset().top;
					    var stickyHeaderTopBar = $('#top-bar').offset().top;

					    $(window).scroll(function(){
					    	if( $(window).scrollTop() > stickyHeaderTopBar ) {
							    $('#top-bar').css({position: 'fixed', top: '0px', left: '50%', margin: '0px auto 0px -500px'});
							    $('#logo').css({marginTop: '43px'});
						    } else {
							    $('#top-bar').css({position: 'static', top: '0px', left: '0', margin: '0 auto'});
							    $('#logo').css({marginTop: '0px'});
						    }

						    if( $(window).scrollTop() + 43 > stickyHeaderTopLinks ) {
							    $('#top-links').css({position: 'fixed', top: '43px', left: '50%', margin: '0px auto 0px -500px'});
							    $('#logo').css({marginTop: '86px'});
						    } else {
							    $('#top-links').css({position: 'static', top: '0px', left: '0', margin: '0 auto'});
						    }
					    });
				    });
			    </script>
	        ";

		    parent::GuiBeginDraw($head);
	    }

        //Draw page header
        public static function GuiDrawHeader()
        {
            $linkList = func_get_args()[0];
            assert('$linkList', "The list of header links is empty!");

            //Calculate a button width according to the total number of links
            $linkCount = count($linkList);
            $linkWidth = $linkCount ? (968 / $linkCount - 20 /*padding*/ - 2 /*separator*/) : 0;
            $linkWidth = floor($linkWidth);

            //Begin drawing the buttons
            ?>
	        <div id="top-bar">
		        <div id="top-bar-left"></div>
		        <div id="top-bar-middle">
				        <form id="tfnewsearch" method="get" action="Search">
					        <input type="text" class="tftextinput" name="" maxlength="120" placeholder="<?php echo Locale::ReturnStrById("szSearchPlaceholder");?>"/>
					        <input type="submit" value="<?php echo Locale::ReturnStrById("szSearchButton");?>" class="tfbutton"/>
				        </form>
				        <div class="user-space">
					        <?php
					            $response = CommonController::TryLoginAndGetUserData($userData);
					            if($response == CommonController::USER_LOGGED_IN)
						            echo "<a href=\"Account\" style=\"padding-right: 5px;\">" . Locale::ReturnStrById("szAccount") . " [ $userData[FullName] ]</a> | <a href=\"Logout\" style=\"padding-left: 5px;\">" . Locale::ReturnStrById("szLogOut") . "</a>";
						        else
						            echo "<a href=\"Login\" style=\"padding-right: 5px;\">" . Locale::ReturnStrById("szLogIn") . "</a> | <a href=\"Register\" style=\"padding-left: 5px;\">" . Locale::ReturnStrById("szSignUp") . "</a>";
					        ?>
				        </div>
				        <div class="tfclear"></div>
		        </div>
		        <div id="top-bar-right"></div>
	        </div>
	        <div id="logo"><a href="Home"><img src="/WebEngine/Apps/Materna/Resources/Textures/logo.gif" width="1000" height="200"/></a></div>
            <div id="top-links">
                        <div id="top-links-left"></div>
                        <div id="top-links-middle">
            <?php echo "\n";

            //Draw each button
            foreach($linkList as $linkItem) { ?>
                            <div class="top-links-sep"></div>
                            <a href="<?php echo $linkItem['href'] ?>">
                                <span class="top-links-item" style="width: <?php echo $linkWidth; ?>px;">
                                    <?php echo Locale::ReturnStrById($linkItem['text']) . "\n" ?>
                                </span>
                            </a>
                            <div class="top-links-sep"></div>
            <?php echo "\n";}

            //End drawing the buttons
            ?>
                        </div>
                        <div id="top-links-right"></div>
                    </div>
            <?php echo "\n";
        }

        //Draw page footer
        public static function GuiDrawFooter()
        {

        }
    }
}
else
    //Wrong theme loaded, print a helpful debug message and die
    DbgHelper::PrintDbgMsgAndDie('Theme "' . Cfg::$appTheme . '" found in cfg.inc, but "' . basename(__FILE__) . '" has been loaded instead!', DbgHelper::RESOURCE);