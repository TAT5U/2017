using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Move : MonoBehaviour 
{
	private Vector3 clickPosition_;

	public void TargetClick()
	{
		clickPosition_ = Input.mousePosition;
	}

	public void TargetRelease()
	{
		GetComponent<Rigidbody2D>().AddForce((clickPosition_ - Input.mousePosition) * 5);
	}
}
