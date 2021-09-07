
namespace Hawk {

	class VertexBuffer;
	class IndexBuffer;

	class VertexArray {
	public:
		virtual ~VertexArray() {};

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void AttachVertexBuffer(const std::shared_ptr<VertexBuffer>& vbuffer) = 0;
		virtual void AttachIndexBuffer(const std::shared_ptr<IndexBuffer>& Ibuffer) = 0;

		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};

}