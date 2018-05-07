using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WarpManager : MonoBehaviour 
{
	private Vector3 pos_ = new Vector3(0.0f, 0.0f, 0.0f);

	private void Update()
	{
		Vector3 warpRotation = new Vector3(0.0f, 0.0f, 10.0f);
		transform.Rotate(warpRotation);
	}

	public Vector3 Warp()
	{
		foreach (Transform child in transform.parent)
		{
			if (child.tag == "Warp" && child.position != transform.position)
			{
				pos_ = child.position;
			}
		}
		return pos_;
	}
}
