<?php
/**
 * Created by PhpStorm.
 * User: Bogdan
 * Date: 2/21/14
 * Time: 11:34 PM
 */

namespace Views;

//Include global config data
require_once('Resources/Config/cfg.inc');
use \Resources\Config\Cfg as Cfg;

//Include theme class
require_once('Resources/Themes/' . Cfg::$appTheme . 'Theme.inc');
use Resources\Themes\Theme as Theme;

//Include Model class
require_once('Models/HomeModel.inc');
use Models\HomeModel as Model;

//Include Controller class
require_once('Controllers/HomeController.inc');
use Controllers\HomeController as Controller;

//The view for the Home page
class HomeView {
    function __construct(Controller $controller, Model $model)
    {
        //Draw the view
        Theme::BeginDraw();
        Theme::DrawHeader();

        Theme::DrawFooter();
        Theme::EndDraw();
    }
}