<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 24/04/14
 * Time: 00:01
 */

namespace Resources\Themes;

//Include configuration data
include_once('Resources/Config/cfg.inc');
use Resources\Config\Cfg as Cfg;

//Interface for theme classes - implementing this
//assures (hopefully) that a new theme does not
//require further code modification elsewhere
use Utils\Debug\DbgHelper;

interface ThemeInterface
{
    public static function GuiBeginDraw();
    public static function GuiEndDraw();
}

class GuiAlignment
{
    const GUI_ALIGN_LEFT    = 0;
    const GUI_ALIGN_RIGHT   = 1;
    const GUI_ALIGN_TOP     = 2;
    const GUI_ALIGN_BOTTOM  = 3;
    const GUI_ALIGN_CENTER  = 4;
}

class GuiBox
{
    public $x1;
    public $y1;
    public $x2;
    public $y2;
    public $alignX;
    public $alignY;

    function __construct($x1, $y1, $x2, $y2, $alignX = GuiAlignment::GUI_ALIGN_LEFT, $alignY = GuiAlignment::GUI_ALIGN_TOP)
    {
	    if(!is_numeric($x1) || !is_numeric($y1) || !is_numeric($x2) || !is_numeric($y2))
	    {
		    $x1 = $y1 = $x2 = $y2 = 0;
		    DbgHelper::PrintDbgMsg("GuiBox parameters are invalid!", DbgHelper::GUI);
	    }

        $this->x1 = $x1;
        $this->y1 = $y1;
        $this->x2 = $x2;
        $this->y2 = $y2;
        $this->alignX = $alignX;
        $this->alignY = $alignY;
    }
}

abstract class ThemeBase implements ThemeInterface
{
    //Draw <head> and start <body>
    public static function GuiBeginDraw($head = "")
    {
        ?>
            <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
                "http://www.w3.org/TR/html4/loose.dtd">
            <html>

                <head>
	                <meta http-equiv="Content-type" content="text/html; charset=UTF-8"/>
                    <title><?php echo Cfg::$appTitle; ?></title>
                    <link rel="stylesheet" type="text/css" href="<?php echo '/WebEngine/Apps/' . Cfg::$appTitle . '/Resources/Styles/style.css'; ?>">
                    <link rel="stylesheet" type="text/css" href="<?php echo '/WebEngine/Resources/Styles/style.css'; ?>">
                    <noscript>
                        Whoops, we detected that your browser does not have JavaScript, or it is disabled.  Our product catalog
                        requires that you have JavaScript enabled to order products.  <a href="http://www.netscape.com">Netscape</a>
                        and <a href="http://www.microsoft.com/ie">Microsoft</a> offer free browsers which support JavaScript.
                        If you are using a JavaScript compliant browser and still have problems, make sure you have JavaScript enabled in
                        your browser's preferences.
                    </noscript>
	                <?php echo $head; ?>
                </head>
                <body>
        <?php
    }

    //Close <body> tag
    public static function GuiEndDraw()
    {
        ?>
                </body>
            </html>
        <?php
    }

    public static function GuiDrawContent(GuiBox $dest, $content, $class = "", $id = "")
    {
        $width = $dest->x2 - $dest->x1;
        $height = $dest->y2 - $dest->y1;
        if(empty($class) && empty($id))
            $class = 'content-base';
        ?>
                    <div <?php
                            if(!empty($class))
                            {
                                echo "\n";
                                echo "                        class=\"";
                                if(is_array($class))
                                {
                                    $i = 0;
                                    foreach($class as $classItem)
                                        echo $classItem . (++$i === count($class) ? "" : " ");
                                }
                                else
                                     echo $class;
                                echo "\"";
                            }?>
                        <?php if(!empty($id)) echo "\n"; ?>
                        <?php if(!empty($id))
                                echo "id=\"$id\""; ?>
                        <?php echo "\n"; ?>
                        style="
                            <?php if($width) echo "width:$width" . "px;" ?>
                            <?php if($height) echo "height:$height" . "px;" ?>
                            <?php
                                if($dest->alignX == GuiAlignment::GUI_ALIGN_LEFT)
                                    echo 'left:' . $dest->x1 . 'px;';
                                else if($dest->alignX == GuiAlignment::GUI_ALIGN_RIGHT)
                                    echo 'right:' . $dest->x1 . 'px;';
                                else if($dest->alignX == GuiAlignment::GUI_ALIGN_CENTER)
                                    echo 'left: 50%; margin-left: ' . ($dest->x1 - $width / 2) . 'px;';
                                else
                                    DbgHelper::PrintDbgMsg("Invalid X alignment: $dest->alignX", DbgHelper::GUI);
                            echo "\n";
                            ?>
                            <?php
                            if($dest->alignY == GuiAlignment::GUI_ALIGN_TOP)
                                echo 'top:' . $dest->y1 . 'px;';
                            else if($dest->alignY == GuiAlignment::GUI_ALIGN_BOTTOM)
                                echo 'bottom:' . $dest->y1 . 'px;';
                            else if($dest->alignY == GuiAlignment::GUI_ALIGN_CENTER)
                                echo 'top: 50%; margin-top: ' . ($dest->y1 - $height / 2) . 'px;';
                            else
                                DbgHelper::PrintDbgMsg("Invalid Y alignment: $dest->alignY", DbgHelper::GUI);
                            ?>">

                                <?php echo $content ?>

                            <?php echo "\n"; ?>
                    </div>
        <?php
        echo "\n";
    }
}
