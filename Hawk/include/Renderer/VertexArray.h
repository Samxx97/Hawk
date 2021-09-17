
namespace Hawk {
	//forward declare to avoid header cyclic depndencies
	class VertexBuffer;
	class IndexBuffer;

	class HAWK_API VertexArray {
	public:
		virtual ~VertexArray() {};

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void AttachVertexBuffer(const Hawk::Ref<VertexBuffer>& vbuffer) = 0;
		virtual void AttachIndexBuffer(const Hawk::Ref<IndexBuffer>& Ibuffer) = 0;

		virtual const Hawk::Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};

}