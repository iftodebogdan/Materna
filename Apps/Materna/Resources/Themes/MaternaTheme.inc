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

//Necessary for retrieving common data from the DB
require_once('Models/CommonModel.inc');
use Models\CommonModel as CommonModel;

//Include configuration data
include_once('Resources/Config/cfg.inc');
use Resources\Config\Cfg as Cfg;

//Include localised string resources
require_once('Apps/' . Cfg::$appTitle . '/Resources/Strings/' . Cfg::$locale . '.inc');
use Resources\Strings\Locale as Locale;

//Include base theme class
require_once('Resources/Themes/ThemeBase.inc');

//Check if the correct theme is loaded
if(strcmp(Cfg::$appTheme, "Materna") == 0)
{
    class Theme implements ThemeBase {
        //private static $stylePath = '/WebEngine/Apps' . Cfg::$appTitle . '/Resources/Styles/Materna/style.css';

        //Draw <head> and start <body>
        public static function BeginDraw()
        {
            ?>

            <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
            "http://www.w3.org/TR/html4/loose.dtd">
            <html>

                <head>
                    <title><?php echo Cfg::$appTitle; ?></title>
                    <link rel="stylesheet" type="text/css" href="<?php echo '/WebEngine/Apps/' . Cfg::$appTitle . '/Resources/Styles/style.css'; ?>">
                    <noscript>
                    Whoops, we detected that your browser does not have JavaScript, or it is disabled.  Our product catalog
                    requires that you have JavaScript enabled to order products.  <a href="http://www.netscape.com">Netscape</a>
                    and <a href="http://www.microsoft.com/ie">Microsoft</a> offer free browsers which support JavaScript.
                    If you are using a JavaScript compliant browser and still have problems, make sure you have JavaScript enabled in
                    your browser's preferences.
                    </noscript>
                </head>
                <body>

            <?php
        }

        //Draw page header
        public static function DrawHeader()
        {
            //Get a list of the top page links and calculate a button width according
            //to the total number of links
            $linkList = array();
            $linkCount = CommonModel::GetHeaderLinks($linkList);
            $linkWidth = $linkCount ? (968 / $linkCount - 20 /*padding*/ - 2 /*separator*/) : 0;
            $linkWidth = floor($linkWidth);

            //Begin drawing the buttons
            ?>

                <div id="top-links">
                    <div id="top-links-left"></div>
                    <div id="top-links-middle">

            <?php

            //Draw each button
            foreach($linkList as $linkItem) {
                ?>

                    <div class="top-links-sep"></div>
                    <a href="<?php echo $linkItem['href'] ?>">
                        <span class="top-links-item" style="width: <?php echo $linkWidth; ?>px;">
                            <?php echo Locale::ReturnStrById($linkItem['text']) ?>
                        </span>
                    </a>
                    <div class="top-links-sep"></div>

                <?php
            }

            //End drawing the buttons
            ?>

                    </div>
                    <div id="top-links-right"></div>

                </div>

            <?php
        }

        //Draw page footer
        public static function DrawFooter()
        {

        }

        //Close <body> tag
        public static function EndDraw()
        {
            ?>

                </body>
            </html>

            <?php
        }
    }
}
else
    //Wrong theme loaded, print a helpful debug message and die
    DbgHelper::printDbgMsgAndDie('Theme "' . Cfg::$appTheme . '" found in cfg.inc, but "' . basename(__FILE__) . '" has been loaded instead!', DbgHelper::RESOURCE);