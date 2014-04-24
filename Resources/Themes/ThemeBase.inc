<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 24/04/14
 * Time: 00:01
 */

namespace Resources\Themes;

//Interface for theme classes - deriving from this
//assures (hopefully) that a new theme does not
//require further code modification elsewhere
interface ThemeBase
{
    public static function BeginDraw();
    public static function DrawHeader();
    public static function DrawFooter();
    public static function EndDraw();
}