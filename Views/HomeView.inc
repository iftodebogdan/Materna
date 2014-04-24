<?php
/**
 * Created by PhpStorm.
 * User: Bogdan
 * Date: 2/21/14
 * Time: 11:34 PM
 */

namespace Views;

require_once('Resources/Config/cfg.inc');

//Include theme class
require_once('Resources/Themes/MaternaTheme.inc');
use Resources\Themes\MaternaTheme as CurrentTheme;

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
        CurrentTheme::BeginDraw();
        CurrentTheme::DrawHeader();

        CurrentTheme::DrawFooter();
        CurrentTheme::EndDraw();
    }
}