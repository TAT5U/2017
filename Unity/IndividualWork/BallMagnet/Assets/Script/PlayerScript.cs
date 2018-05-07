using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PlayerScript : MonoBehaviour
{
	private float moveX = 0.0f;
	private float collisionWallX = 0.0f;

	public CreateManagementScript objController;
	public ScoreScript score;

	private bool isCollisionWall = false;

	void Update()
	{
		if (gameObject.tag != "Magnet")
		{
			GetMove();
			if (collisionWallX < moveX && (Input.GetKey(KeyCode.D) || Input.GetKey(KeyCode.RightArrow)))
			{
				isCollisionWall = false;
			}
			else if (collisionWallX > moveX && (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.LeftArrow)))
			{
				isCollisionWall = false;
			}

			gameObject.GetComponent<Rigidbody>().AddForce(new Vector3(moveX, 0, 0), ForceMode.Force);
		}
	}

	private void GetMove()
	{
		moveX = Input.GetAxis("Horizontal");
		if (moveX >= 1.0f || moveX <= -1.0f)
		{
			collisionWallX = moveX;
		}
	}

	public float GetPlayerTransformX()
	{
		return moveX;
	}

	public bool GetIsCollisionWall()
	{
		return isCollisionWall;
	}


	void OnCollisionEnter(Collision col)
	{
		if (col.gameObject.tag == "Field")
		{
			gameObject.GetComponent<Rigidbody>().constraints = RigidbodyConstraints.FreezeAll;
		}

		if (col.gameObject.tag == "Wall")
		{
			isCollisionWall = true;
		}

		if (col.gameObject.tag == "Ally")
		{
			if (gameObject.tag != "Magnet")
			{
				score.SetScore(10);
				objController.MagnetBallNectObjectCall();
			}
			else
			{
				gameObject.transform.root.GetChild(0).GetComponent<PlayerScript>().score.SetScore(10);
				gameObject.transform.root.GetChild(0).GetComponent<PlayerScript>().objController.MagnetBallNectObjectCall();
			}
			col.gameObject.transform.GetComponent<Rigidbody>().constraints = RigidbodyConstraints.FreezeAll;
			col.gameObject.tag = "Magnet";
			col.gameObject.AddComponent<PlayerScript>();
			col.gameObject.transform.SetParent(gameObject.transform);
		}
		if (col.gameObject.tag == "Enemy")
		{
			if (gameObject.tag != "Magnet")
			{
				score.ScoreWrite();
			}
			else
			{
				gameObject.transform.root.GetChild(0).GetComponent<PlayerScript>().score.ScoreWrite();
			}
			SceneManager.LoadScene(2);
		}
	}
}
