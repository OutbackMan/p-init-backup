typedef struct {
	bitarray* component_mask;

	DisplacementComponent* displacement_component;
} EntityManager;

unsigned create_entity(EntityManager* entity_manager)
{
	unsigned entity = 0;

	for (unsigned entity_index = 0; entity_index < ; ++entity_index) {
		if (bit_array_get(entity_manager->component_mask, entity_index) == COMPONENT_NONE) {
			return entity_index;	
		}
	}

	// no entities left
	return entity;
}
