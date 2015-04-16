<?php
// Do not modify the Shipping class.

abstract class Shipping {

	private $_itemsCount;
	private $_distance;

	public function __construct($itemsCount, $distance) {

		$this->_itemsCount = $itemsCount;

		$this->_distance = $distance;

	}

	abstract public function getFees();

	public function getDistance() {

		return $this->_distance;

	}

	public function getItemsCount(){

		return $this->_itemsCount;

	}

}

// You can modify code below this comment.

class InternationalShipping extends Shipping {

	private $_internationalDistance;

	public function __construct($itemsCount, $distance, $internationalDistance){

		parent::__construct($itemsCount, $distance);

		$this->_internationalDistance = $internationalDistance;

	}

	public function getFees(){

		$no_of_items = $this->getItemsCount();

		$local_distance = $this->getDistance();

		$international_distance = $this->_internationalDistance;

		$fees = $no_of_items * ($local_distance * 0.8 + $international_distance * 1.2);

		return $fees;

	}

}

class LocalShipping extends Shipping {

	public function getFees(){

		$no_of_items = $this->getItemsCount();

		$local_distance = $this->getDistance();

		$fees = $no_of_items * $local_distance * 0.8;

		return $fees;

	}

}

function calculateShippingFees($items) {

// To print results to the standard output you can use print

// Example:

// print “Hello world!”;

	$total = 0;

	foreach ($items as $key => $object) {

	# code…

		if($object instanceof Shipping){

			$total += $object->getFees();

		} else {

			$total += 0;

		}

	}

	echo $total;

}

// Do NOT call the calculateShippingFees function in the code

// you write. The system will call it automatically.

?>