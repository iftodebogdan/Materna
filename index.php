<?php
/**
 * Created by PhpStorm.
 * User: Bogdan
 * Date: 2/21/14
 * Time: 8:27 PM
 */

//Include debug functions
require_once('Utils/Debug/DbgHelper.inc');
use \Utils\Debug\DbgHelper as DbgHelper;

//Include Cfg class to access configuration data
require_once('Resources/Config/cfg.inc');
use \Resources\Config\Cfg as Cfg;

//Check if there is a QUERY_STRING index
if(!array_key_exists('QUERY_STRING', $_SERVER) || !strlen($_SERVER['QUERY_STRING']))
{
    //DbgHelper::PrintDbgMsgAndDie('Index QUERY_STRING does not exist in $_SERVER!', DbgHelper::ERROR);
    $_SERVER['QUERY_STRING'] = 'Home';
}

//Parse the QUERY_STRING
$params = explode('/', $_SERVER['QUERY_STRING']);

//Sanitize input
$params = array_filter($params, 'strlen');

//Check if the user arguments are valid
if( count($params) )
{
    //Build class names
    $modelClass = $params[0] . 'Model';
    $viewClass = $params[0] . 'View';
    $controllerClass = $params[0] . 'Controller';

    //Check if the files exist
    if( file_exists('Apps/' . Cfg::$appTitle . '/Models/' . $modelClass . '.inc') &&
        file_exists('Apps/' . Cfg::$appTitle . '/Views/' . $viewClass . '.inc') &&
        file_exists('Apps/' . Cfg::$appTitle . '/Controllers/' . $controllerClass . '.inc') )
    {
        //Include class definitions
        require_once('Apps/' . Cfg::$appTitle . '/Models/' . $modelClass . '.inc');
        require_once('Apps/' . Cfg::$appTitle . '/Views/' . $viewClass . '.inc');
        require_once('Apps/' . Cfg::$appTitle . '/Controllers/' . $controllerClass . '.inc');


        //Add namespaces to class names
        $modelClass = '\Models\\' . $modelClass;
        $viewClass = '\Views\\' . $viewClass;
        $controllerClass = '\Controllers\\' . $controllerClass;

	    //Start PHP session
	    session_start();

        //Instantiate modules
        $model = new $modelClass();
        $controller = new $controllerClass($model);
        $view = new $viewClass($controller, $model);
    }
    else
        //At least one file does not exist
        DbgHelper::PrintDbgMsgAndDie('Could not find the \'' . $params[0] . '\' MVC model!', DbgHelper::APP);
}
else
    //There are no user arguments
    DbgHelper::PrintDbgMsgAndDie('There are no app parameters!', DbgHelper::ERROR);

DbgHelper::FlushDbgOutputBuffer();