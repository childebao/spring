/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */


#include "TracerProjectile.h"
#include "Rendering/GL/myGL.h"

CR_BIND_DERIVED(CTracerProjectile, CProjectile, )

CR_REG_METADATA(CTracerProjectile,
(
	CR_MEMBER(speedf),
	CR_MEMBER(drawLength),
	CR_MEMBER_BEGINFLAG(CM_Config),
		CR_MEMBER(length),
	CR_MEMBER_ENDFLAG(CM_Config),
	CR_RESERVED(8)
));

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTracerProjectile::CTracerProjectile(const float3& pos, const float3& speed, const float range, CUnit* owner):
	CProjectile(pos, speed, owner, false, false, false)
	, length(range)
	, drawLength(0.0f)
{
	SetRadiusAndHeight(1.0f, 0.0f);
	checkCol = false;

	speedf = this->speed.Length();
	dir = this->speed / speedf;
}

CTracerProjectile::CTracerProjectile()
	: speedf(0.0f)
	, length(0.0f)
	, drawLength(0.0f)
{
	checkCol = false;
}

void CTracerProjectile::Init(const float3& pos, CUnit* owner)
{
	speedf = speed.Length();
	if (speedf == 0.0f) {
		speed = RgtVector;
	}
	dir = speed / speedf;

	CProjectile::Init(pos, owner);
}

CTracerProjectile::~CTracerProjectile()
{

}

void CTracerProjectile::Update()
{
	pos += speed;

	drawLength += speedf;
	length -= speedf;
	if (length < 0) {
		deleteMe = true;
	}
}

void CTracerProjectile::Draw()
{
	if (drawLength > 3) {
		drawLength = 3;
	}

	glTexCoord2f(1.0f/16, 1.0f/16);
	glColor4f(1, 1, 0.1f, 0.4f);
	glBegin(GL_LINES);
		glVertexf3(drawPos);
		glVertexf3(drawPos-dir * drawLength);
	glEnd();
	glColor4f(1, 1, 1, 1);
	glTexCoord2f(0, 0);
}
