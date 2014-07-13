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

//Include base theme class
require_once('Resources/Themes/ThemeBase.inc');

//Check if the correct theme is loaded
if(strcmp(Cfg::$appTheme, "Materna") == 0)
{
    class Theme extends ThemeBase {
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