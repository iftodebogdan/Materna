<?php
/**
 * Created by PhpStorm.
 * User: Sorrell
 * Date: 05/08/14
 * Time: 04:21
 */

namespace Views;

abstract class ViewBase
{
	protected $controller;
	protected $model;

	function __construct($controller, $model)
	{
		$this->controller = $controller;
		$this->model = $model;

		$this->Init();
		$this->Draw();
	}

	abstract protected function Init();
	abstract protected function Draw();
} 